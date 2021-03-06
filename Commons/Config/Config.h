//
// Copyright(c) 2016 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#pragma once
#include <string>
#include <map>

enum class Verbosity {
  Simple,
  Normal,
  Verbose,
  Default
};

struct Config {
  unsigned int hotkey_ = 0x79; // F10
  unsigned int toggleOverlayHotKey_ = 0x78; // F9
  unsigned int toggleGraphOverlayHotKey_ = 0x76;  // F7
  unsigned int toggleBarOverlayHotKey_ = 0x77;  // F8
  unsigned int recordingTime_ = 0;
  bool recordAllProcesses_ = true;
  unsigned int overlayPosition_ = 2;

  float startDisplayTime_ = 1.0f;
  float endDisplayTime_ = 10.0f;

  bool Load(const std::wstring& path);
};

struct ProviderConfig
{
  Verbosity recordingDetail = Verbosity::Verbose;
  bool enabled = true;
};

struct ConfigCapture {
  std::map<std::string, ProviderConfig> provider;

  bool Load(const std::wstring& path);

private:
  void CreateDefault(const std::wstring& fileName);
};