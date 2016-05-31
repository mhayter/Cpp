#ifndef __CODEFORCES_IO__
#define __CODEFORCES_IO__
// Adapted from http://codeforces.com/blog/entry/8080
namespace CodeForcesIO {
	static char stdinBuffer[1024];
	static char* stdinDataEnd = stdinBuffer + sizeof (stdinBuffer);
	static const char* stdinPos = stdinDataEnd;

	void readAhead(size_t amount)
	{
	    size_t remaining = stdinDataEnd - stdinPos;
	    if (remaining < amount) {
	       memmove(stdinBuffer, stdinPos, remaining);
	       size_t sz = fread(stdinBuffer + remaining, 1, sizeof (stdinBuffer) - remaining, stdin);
	       stdinPos = stdinBuffer;
	       stdinDataEnd = stdinBuffer + remaining + sz;
	       if (stdinDataEnd != stdinBuffer + sizeof (stdinBuffer))
	         *stdinDataEnd = 0;
	    }
	}

	int readInt()
	{
	    readAhead(16);

	    int x = 0;
	    bool neg = false;
	    while (*stdinPos <'-') ++stdinPos;

	    if (*stdinPos == '-') {
	       ++stdinPos;
	       neg = true;
	    }

	    while (*stdinPos >= '0' && *stdinPos <= '9') {
	       x *= 10;
	       x += *stdinPos - '0';
	       ++stdinPos;
	    }


	    return neg ? -x : x;
	}
}
#endif