class Solution {
public:
	vector<string> long_urls;

	pair<string, string> split_url(const string &s) {
		const char *p = strrchr(s.c_str(), '/');
		int off = p - s.c_str();
		return make_pair(s.substr(0, off), s.substr(off + 1, s.size() - off - 1));
	}

	// Encodes a URL to a shortened URL.
	string encode(string longUrl) {
		int sz = long_urls.size();
		pair<string, string> pss = split_url(longUrl);
		char buf[BUFSIZ];
		sprintf(buf, "%s/%06x", pss.first.c_str(), sz);
		long_urls.push_back(longUrl);
		return buf;
	}

	// Decodes a shortened URL to its original URL.
	string decode(string shortUrl) {
		pair<string, string> pss = split_url(shortUrl);
		int idx;
		sscanf(pss.second.c_str(), "%06x", &idx);
		return long_urls[idx];
	}
};
