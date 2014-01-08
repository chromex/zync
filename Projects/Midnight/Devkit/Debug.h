// Copyright (c) 2013 Loren Hoffman
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// TODO: Log file support

class Debug
{
public:
	Debug()
		: _logLevel(E_INFO)
	{
	}

	~Debug()
	{
	}

	enum LogLevel 
	{
		E_ERROR,
		E_WARNING,
		E_INFO,
		NumLogLevels
	};

	void SetLogLevel(LogLevel level)
	{
		assert(LogLevelValid(level));

		this->_logLevel = level;
	}

	void Error(const std::string& message)
	{
		this->WriteMessage(E_ERROR, message);
	}

	void Warning(const std::string& message)
	{
		this->WriteMessage(E_WARNING, message);
	}

	void Log(const std::string& message)
	{
		this->WriteMessage(E_INFO, message);
	}

	void Assert(bool value, const char* reason)
	{
		if(!value)
		{
			this->Error(reason);
		}
	}

private:
	void WriteMessage(LogLevel level, const std::string& message)
	{
		assert(LogLevelValid(level));

		if (level > this->_logLevel)
		{
			return;
		}

		static const char* levelNames[] = { "Error", "Warning", "Info" };

		std::stringstream ss;
		ss << "[" << levelNames[level] << "] " << message << std::endl;
		std::cout << ss.str() << std::flush;

		if(level == E_ERROR)
		{
			exit(EXIT_FAILURE);
		}
	}

	static bool LogLevelValid(LogLevel level)
	{
		return level >= 0 && level < NumLogLevels;
	}

	int _logLevel;
};