// 学习的点：
// 1. 先考虑大致的业务流程，而不是复杂的算法，很多时候没有复杂的算法，或者算法仅仅是流程的一部分。
// 2. 分析什么流程是必不可少的，比如你需要取每个 followee，这个迭代必不可少，但是结合算法，你可以通过 heap 和链表在 O(log n)取得最大时间值。
// 3. 小心插入过程中的迭代器失效。
class Tweet {
public:
	int user_id, tweet_id;
	int time;
	Tweet *next;

	Tweet(int user_id, int tweet_id) : user_id(user_id), tweet_id(tweet_id), next(NULL) {
		static int s_time = 0;
		time = s_time++;
	}
};

class User {
public:
	int user_id;
	unordered_set<int> followees;
	Tweet *tweet;

	User(int userid) : user_id(userid), tweet(NULL) {
		followees.insert(user_id);
	}
};

class Twitter {
public:
	unordered_map<int, User> uid2u;

	/** Initialize your data structure here. */
	Twitter() {
	}

	User &user(int uid) {
		unordered_map<int, User>::iterator it = uid2u.find(uid);
		if (it != uid2u.end())
			return it->second;
		else {
			User u(uid);
			uid2u.insert(make_pair(uid, u));
			return uid2u.find(uid)->second; // ATTENTION: ITERATOR `it` HAS CHANGED!
		}
	}

	/** Compose a new tweet. */
	void postTweet(int uid, int tid) {
		User &u = user(uid);
		Tweet *t = u.tweet;
		u.tweet = new Tweet(uid, tid);
		u.tweet->next = t;
	}

	class Comparator {
	public:
		bool operator()(const Tweet *t1, const Tweet *t2) const {
			return t1->time < t2->time;
		}
	};

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int uid) {
		User u = user(uid);
		const unordered_set<int> &followees = u.followees;

		priority_queue<Tweet *, vector<Tweet *>, Comparator> pq;
		for (int uid2 : followees) {
			User &u2 = user(uid2);
			if (u2.tweet)
				pq.push(u2.tweet);
		}

		vector<int> rv;
		while (rv.size() < 10 && !pq.empty()) {
			Tweet *t = pq.top();
			pq.pop();
			if (t->next) {
				pq.push(t->next);
			}
			rv.push_back(t->tweet_id);
		}
		return rv;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int uid1, int uid2) {
		User &u1 = user(uid1);
		User &u2 = user(uid2);
		u1.followees.insert(uid2);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int uid1, int uid2) {
		if (uid1 == uid2) // WHAT THE FUCK... STUPID CASE.
		    return;
		User &u1 = user(uid1);
		u1.followees.erase(uid2); // ATTENTION: YOU CAN'T USE `std::map[key]` WITHOUT VALUE TYPE DEFAULT CONSTRUCTOR
	}
};
