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

//////////////////////////////////////////////////////////////////////
// All user visible classes are encapsulated in a wrapper class to
// protect against binary compatability.
//////////////////////////////////////////////////////////////////////

#include <string>

#include <string.h>

#include "pluton/client.h"

#include "util.h"
#include "clientImpl.h"
#include "serviceImpl.h"
#include "requestImpl.h"

pluton::clientRequest::clientRequest()
  : _impl(new pluton::clientRequestImpl())
{
}

pluton::clientRequest::~clientRequest()
{
  delete _impl;
}

void
pluton::clientRequest::reset()
{
  _impl->reset();
}

void
pluton::clientRequest::setRequestData(const char* request)
{
  _impl->setRequestData(request, strlen(request));
}

void
pluton::clientRequest::setRequestData(const char* request, int len)
{
  _impl->setRequestData(request, len);
}

void
pluton::clientRequest::setRequestData(const std::string& request)
{
  _impl->setRequestData(request);
}

pluton::faultCode
pluton::clientRequest::getResponseData(const char*& cp, int& len) const
{
  return _impl->getResponseData(cp, len);
}

pluton::faultCode
pluton::clientRequest::getResponseData(std::string& resp) const
{
  return _impl->getResponseData(resp);
}

bool
pluton::clientRequest::setContext(const char* key, const std::string& value)
{
  return _impl->setContext(key, value);
}

bool
pluton::clientRequest::hasFault() const
{
  return _impl->hasFault();
}

pluton::faultCode
pluton::clientRequest::getFault(std::string& fault) const
{
  return _impl->getFault(fault);
}

pluton::faultCode
pluton::clientRequest::getFaultCode() const
{
  return _impl->getFaultCode();
}

std::string
pluton::clientRequest::getFaultText() const
{
  return _impl->getFaultText();
}

std::string
pluton::clientRequest::getServiceName() const
{
  return _impl->getServiceName();
}

bool
pluton::clientRequest::inProgress() const
{
  return _impl->inProgress();
}

void
pluton::clientRequest::setAttribute(pluton::requestAttributes A)
{
  _impl->setAttribute(A);
}

void
pluton::clientRequest::clearAttribute(pluton::requestAttributes A)
{
  _impl->clearAttribute(A);
}

bool
pluton::clientRequest::getAttribute(pluton::requestAttributes A)
{
  return _impl->getAttribute(A);
}


void
pluton::clientRequest::setClientHandle(void *v)
{
  _impl->setClientHandle(v);
}

void*
pluton::clientRequest::getClientHandle() const
{
  return _impl->getClientHandle();
}
