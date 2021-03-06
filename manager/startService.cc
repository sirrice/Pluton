/*
Copyright (c) 2010, Yahoo! Inc. All rights reserved.

Redistribution and use of this software in source and binary forms, with or
without modification, are permitted provided that the following conditions are
met: 

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.

* Neither the name of Yahoo! Inc. nor the names of its contributors may be used 
to endorse or promote products derived from this software without specific prior 
written permission of Yahoo! Inc.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#include <iostream>

#include <st.h>

#include "debug.h"
#include "logging.h"
#include "util.h"

#include "manager.h"
#include "service.h"
#include "process.h"

using namespace std;


//////////////////////////////////////////////////////////////////////
// The thread wrapper for a service. Create and run.
//////////////////////////////////////////////////////////////////////

static void*
serviceHandlerThread(void* voidS)
{
  service* S = static_cast<service*>(voidS);

  if (debug::service()) DBGPRT << "Service started: " << S->getLogID() << endl;

  S->preRun();
  S->run();
  S->runUntilIdle();

  if (S->error()) LOGPRT << "Service Error: "
			 << S->getLogID() << " " << S->getErrorMessage() << endl;

  if (debug::process()) DBGPRT << "Service shutting down: " << S->getLogID() << endl;

  S->completeShutdownSequence();

  string id = S->getLogID();		// Save across destroy
  S->getParent()->destroyOffspring(S);	// Tell parent to destroy my object

  if (debug::service()) DBGPRT << "Service shutdown complete: " << id << endl;

  return 0;
}


//////////////////////////////////////////////////////////////////////

bool
service::startThread(service* S)
{
  S->setThreadID(st_thread_create(serviceHandlerThread, (void*) S, 0,
				  S->getMANAGER()->getStStackSize()));
  if (debug::thread()) DBGPRT << "Service Start: " << S->getThreadID() << endl;

  return true;
}
