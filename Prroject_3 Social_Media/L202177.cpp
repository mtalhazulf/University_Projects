#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class sm {
public:
	sm()
	{

	}
	virtual void setid(string id) = 0;
	virtual string getid() = 0;
	virtual string retname() = 0;
	virtual ~sm()
	{
	}
};

class pages : virtual public sm
{
protected:
	string id, name;
public:
	pages()
	{

	}
	pages(string _id)
	{
		id = _id;
	}
	pages(string _id, string title) :name(title)
	{
		id = _id;
	}
	void printid()
	{
		cout << id;
	}
	void print()
	{
		cout << "\nID : " << id << "\nTitle : " << name << endl;
	}
	void setid(string _id)
	{
		id = _id;
	}
	string getid()
	{
		return id;
	}
	string retname()
	{
		return name;
	}
	pages operator = (pages& obj)
	{
		this->id = obj.id;
		if ((obj.name[0] >= 65 || obj.name[0] <= 122))
		{
			this->name = obj.name;
		}
		return *this;
	}
	bool findid(string target)
	{
		if (target == id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string returntitlebyid() {
		return name;
	}
	void searchname(string word, bool& found, string& uid, string& foundlist)
	{
		bool match = false;
		int counter = 0;
		for (int i = 0; i < name.size(); i++)
		{
			for (int j = 0; j < word.size(); j++)
			{
				if (name[i] == word[j])
				{
					i++;
					counter++;
					match = true;
					if (counter == word.size())
					{
						break;
					}
				}
				else
				{
					counter = 0;
					match = false;
				}
				if (j == word.size() - 1)
				{
					match = false;
				}
				if (i == name.size() - 1)
				{
					match = false;
					counter = 0;
					break;
				}
			}
			if (match == true)
			{
				break;
			}
		}
		if (match)
		{
			found = true;
			uid = id;
			foundlist = name;
		}
	}
	~pages()
	{
	}
};

class user : virtual public sm
{
protected:
	string userid;
	string firstname;
	string lastname;
	string** friendlist = nullptr;
	int friendcount = 0;
	pages** liked = nullptr;
	int likedpagescount = 0;

public:
	void init()
	{
		liked = nullptr;
		friendlist = nullptr;
		friendcount = 0;
		likedpagescount = 0;
	}

	user()
	{
		init();
	}

	user(string usid, string fn, string ln, string**& frndlist, int frndcnt, pages**& lp, int pgcnt)
	{
		userid = usid;
		firstname = fn;
		lastname = ln;
		friendlist = frndlist;
		friendcount = frndcnt;
		friendlist = new string * [frndcnt];
		for (int i = 0; i < frndcnt; i++)
		{
			friendlist[i] = new string[2];
			friendlist[i][0] = frndlist[i][0];
		}
		likedpagescount = pgcnt;
		liked = new pages * [pgcnt];
		for (int i = 0; i < pgcnt; i++)
		{
			liked[i] = new pages[1];
			liked[i][0].setid(lp[i][0].getid());
		}
	}

	void print()
	{
		cout << userid << "\t" << firstname << " " << lastname << " ";
		for (int i = 0; i < friendcount; i++)
		{
			cout << friendlist[i][0];
			cout << friendlist[i][1];

			cout << " ";
		}
		cout << " -1 ";
		for (int i = 0; i < likedpagescount; i++)
		{
			liked[i][0].print();
			cout << " ";
		}
	}

	bool  findid(string target)
	{
		if (target == userid)
		{
			return true;
		}
		return false;
	}

	pages**& getlikedpages(int& size)
	{
		size = likedpagescount;
		return liked;
	}

	string**& getfriendlist(int& size)
	{
		size = friendcount;
		return friendlist;
	}

	void addfrndlist(string id)
	{
		if (friendcount < 10)
		{
			extend(friendlist, friendcount);
			friendlist[friendcount] = new string[2];
			for (int j = 0; j < id.size(); j++)
			{
				friendlist[friendcount][j] = id[j];
			}
			friendcount++;
		}
		else
		{
			cout << "Cant enter friend. MaX Friend Reach.";
		}
		
	}

	void addpglist(string id)
	{
		extend(liked, likedpagescount);
		liked[likedpagescount] = new pages[2];
		liked[likedpagescount][0].setid(id);
	}


	template<typename t>
	void extend(t**& arr, int size)
	{
		if (size > 0)
		{
			t** temp = new t * [size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = new t * [size + 1];
			for (int i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
		}
		else
		{
			arr = new t * [size + 1];
		}
	}

	void setpage(int i, string id)
	{
		liked[i][0].setid(id);
	}

	void setid(string id)
	{
		userid = id;
	}

	string getid()
	{
		return userid;
	}

	void getpage(int i)
	{
		cout << liked[i][0].getid();
	}

	template<typename t>
	void extend(t*& arr, int size)
	{
		if (size > 0)
		{
			t* temp = new t[size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = new t[size + 1];
			for (int i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
		}
		else
		{
			arr = new t[size + 1];
		}
	}

	string retname()
	{
		return (firstname + "  " + lastname);
	}

	void searchname(string word, bool& found, string& id, string& foundlist)
	{
		string name = firstname + " " + lastname;
		bool match = false;
		int counter = 0;
		for (int i = 0; i < name.size(); i++)
		{
			for (int j = 0; j < word.size(); j++)
			{
				if (name[i] == word[j])
				{
					i++;
					counter++;
					match = true;
					if (counter == word.size())
					{
						break;
					}
				}
				else
				{
					counter = 0;
					match = false;
				}
				if (j == word.size() - 1 && (match == false))
				{
					match = false;
				}
				if (i == name.size() - 1 && (match == false))
				{
					match = false;
					counter = 0;
					break;
				}
			}
			if (match == true && counter == word.size())
			{
				break;
			}
			else
			{
				counter = 0;
				match = false;
			}
		}
		if (match)
		{
			found = true;
			id = userid;
			foundlist = name;
		}
	}
	~user()
	{
		if (liked != nullptr)
		{
			for (int i = 0; i < likedpagescount; i++)
			{
				delete [] liked[i];
			}
			delete[] liked;
			liked = nullptr;
			likedpagescount = 0;
		}
		if (friendlist != nullptr)
		{
			for (int i = 0; i < friendcount; i++)
			{
				delete [] friendlist[i];
			}
			delete[] friendlist;
			friendlist = nullptr;
			friendcount = 0;
		}
	}
};

class comments {
	string commentid;
	string postid;
	string commentby;
	string comment;
public:
	comments()
	{
	}
	comments(string cid, string pid, string cby, string cmnt)
	{
		commentid = cid;
		postid = pid;
		commentby = cby;
		comment = cmnt;
	}
	void print()
	{
		cout << "Comment ID : " << commentid << "\nPost ID : " << postid << endl;
		cout << "Comment By : " << commentby << "\n";
		cout << "Comment : " << comment << endl;
	}
	bool findid(string pid)
	{
		if (pid == postid)
		{
			return true;
		}
		return false;
	}
	void getcmnt(string& cmnt, string& cmntr)
	{
		cmnt = comment;
		cmntr = commentby;
	}

	~comments()
	{

	}
};

class date {
	string dates;

public:
	int day = 0, month = 0, year = 0;
	date()
	{

	}
	date(string _date)
	{
		dates = _date;
		//datacorrect();
	}
	void datacorrect()
	{

	datecheck:
		if (dates.size() == 10)
		{
			day = ((dates[0] - 48) * 10) + (dates[1] - 48);
			if (dates[2] != 47)
			{

				cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
				cin >> dates;

				goto datecheck;
			}
			month = ((dates[3] - 48) * 10) + (dates[4] - 48);
			if (dates[5] != 47)
			{
				cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
				cin >> dates;

				goto datecheck;
			}
			year = ((dates[6] - 48) * 1000) + ((dates[7] - 48) * 100) + ((dates[8] - 48) * 10) + (dates[9] - 48);
		}
		else if (dates.size() == 9)
		{
			if ((dates[0] > 48 && dates[0] < 58) && (dates[1] > 48 && dates[1] < 58))
			{
				day = ((dates[0] - 48) * 10) + (dates[1] - 48);
				if (dates[2] == 47)
				{
					cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
					cin >> dates;

					goto datecheck;
				}
				else
				{
					if ((dates[3] > 48 && dates[3] < 58) && (dates[4] > 48 && dates[4] < 58))
					{
						month = ((dates[3] - 48) * 10) + (dates[4] - 48);
					}
					else if ((dates[3] > 48 && dates[3] < 58) && dates[4] == 57)
					{
						month = (dates[3] - 48);
						year = ((dates[5] - 48) * 1000) + ((dates[6] - 48) * 100) + ((dates[7] - 48) * 10) + (dates[8] - 48);
					}
					else
					{
						cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
						cin >> dates;
						goto datecheck;
					}
				}
			}
			else if ((dates[0] > 48 && dates[0] < 58) && dates[1] == 47)
			{
				day = (dates[0] - 48);
				if ((dates[2] > 48 && dates[2] < 58) && (dates[3] > 48 && dates[3] < 58))
				{
					month = ((dates[2] - 48) * 10) + (dates[3] - 48);
				}
				else if ((dates[2] > 48 && dates[2] < 58) && dates[3] == 47)
				{
					month = (dates[2] - 48);

					year = ((dates[4] - 48) * 1000) + ((dates[5] - 48) * 100) + ((dates[6] - 48) * 10) + (dates[7] - 48);
				}
				else
				{
					cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
					cin >> dates;
					goto datecheck;
				}

			}
			else
			{
				cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
				cin >> dates;
				goto datecheck;
			}
			month = ((dates[3] - 48) * 10) + (dates[4] - 48);
			year = ((dates[6] - 48) * 1000) + ((dates[7] - 48) * 100) + ((dates[8] - 48) * 10) + (dates[9] - 48);
		}
		else if (dates.size() == 8)
		{
			if ((dates[0] > 48 && dates[0] < 58) && dates[1] == 47)
			{
				if ((dates[2] > 48 && dates[2] < 58) && dates[3] == 47)
				{
					day = (dates[0] - 48);
					month = (dates[2] - 48);
					year = ((dates[4] - 48) * 1000) + ((dates[5] - 48) * 100) + ((dates[6] - 48) * 10) + (dates[7] - 48);
				}
				else
				{
					cout << "You have entered the wrong date. Kindly Re-enter Format dd/mm/yyyy : ";
					cin >> dates;
					goto datecheck;
				}
			}
			else
			{
				cout << "You have entered the wrong date. Kindly Re-enter Format dd/mm/yyyy : ";
				cin >> dates;
				goto datecheck;
			}
		}
		if (day > 31 || day < 1)
		{
			cout << "You have entered the wrong date. Kindly Re-enter Format dd/mm/yyyy : ";
			cin >> dates;
			goto datecheck;
		}
		if (month > 12 || month < 1)
		{
			cout << "You have entered the wrong month. Kindly Re-enter Format dd/mm/yyyy  : ";
			cin >> dates;
			goto datecheck;
		}
		if (year < 2000 || year > 2100)
		{
			cout << "you have entered the Year. Year should be Year>2000 && Year < 2100 .";
			cin >> dates;
			goto datecheck;
		}
	}

	void entry(string _date)
	{
		dates = _date;
		//datacorrect();
	}
	void print()
	{
		cout << day << " / " << month << " / " << year << endl;
	}

	void operator = (date& temp)
	{
		day = temp.day;
		month = temp.month;
		year = temp.year;
	}

	string getdate()
	{
		return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}
};

class post {
	string postid;
	date shareddate;
	string postcont;
	int activity;
	string acttype;
	sm* sharedby;
	int like_by = 0;
	sm** likedby;
public:
	void init()
	{
		sharedby = nullptr;
		likedby = nullptr;
	}
	post()
	{
		init();
	}
	post(string id, date _shareddate, string postcn, int toa, string atp, string shby, string* likes, int likecnt)
	{
		postid = id;
		shareddate = _shareddate;
		postcont = postcn;
		activity = toa;
		acttype = atp;
		like_by = likecnt;
		if (shby[0] == 'p')
		{
			sharedby = new pages[1];
		}
		else if (shby[0] == 'u')
		{
			sharedby = new user[1];
		}
		sharedby[0].setid(shby);

		likedby = new sm * [like_by];

		for (int i = 0; i < like_by; i++)
		{
			if (likes[i][0] == 'p')
			{
				likedby[i] = new pages[1];
			}
			else
			{
				likedby[i] = new user[1];
			}
			likedby[i][0].setid(likes[i]);
		}
	}
	void print()
	{
		cout << "Post ID : " << postid << endl;
		cout << "Shared Date : " << shareddate.day << " - " << shareddate.month << " - " << shareddate.year << endl;
		cout << "Content : " << postcont << endl;
		cout << activity << "   " << acttype << endl;
		cout << "Shared By : " << sharedby[0].getid() << endl;
		cout << "Liked by : ";
		for (int i = 0; i < like_by; i++)
		{
			cout << likedby[i][0].getid() << "  ";
		}
		cout << endl;
	}
	void printactivity()
	{
		switch (activity)
		{
		case 0:
			cout << " Shared \"" << postcont << "\"";
			break;
		case 1:
			cout << " is feeling " << acttype << endl << "     \"" << postcont << "\"";
			break;
		case 2:
			cout << " is thinking about " << acttype << endl << "     \"" << postcont << "\"";
			break;
		case 3:
			cout << " is making " << acttype << endl << "     \"" << postcont << "\"";
			break;
		case 4:
			cout << " is Celebrating " << acttype << endl << "     \"" << postcont << "\"";
			break;
		}
	}

	template<typename t>
	void extend(t**& arr, int size)
	{
		if (size > 0)
		{
			t** temp = new t * [size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = new t * [size + 1];
			for (int i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
		}
		else
		{
			arr = new t * [size + 1];
		}
	}

	int getact()
	{
		return activity;
	}
	string gettoa()
	{
		return acttype;
	}
	void likepost(string uid)
	{
		if (like_by >= 10)
		{
			cout << "\nCan not Like the Post. MAX Liked Reached." << endl;
		}
		else
		{
			extend(likedby, like_by);
			if (uid[0] == 'p')
			{
				likedby[like_by] = new pages;
				likedby[like_by][0].setid(uid);
				like_by++;
				cout << "Post Liked." << endl;
			}
			else if (uid[0] == 'u')
			{
				likedby[like_by] = new user;
				likedby[like_by][0].setid(uid);
				like_by++;
				cout << "Post Liked." << endl;
			}

		}

	}
	sm**& printpost(string& id, int& likes)
	{
		likes = like_by;
		id = postid;
		printactivity();
		return likedby;
	}
	void printpostwol(date& temp)
	{
		printactivity();
		temp = shareddate;
	}
	string getshare()
	{
		return sharedby[0].getid();
	}
	sm**& fetchlikes(int& likes)
	{
		likes = like_by;
		return likedby;
	}

	void printids()
	{
		sharedby[0].getid();
	}
	bool findshareduser(string id)
	{
		if (id == sharedby[0].getid())
		{
			return true;
		}
		return false;
	}
	string getdate()
	{
		return shareddate.getdate();
	}
	string getpostid()
	{
		return postid;
	}
	bool findid(string pid)
	{
		if (pid == postid)
		{
			return true;
		}
		return false;
	}
	void getintdate(date& tempdate)
	{
		tempdate = shareddate;
	}
	string getcnt()
	{
		return postcont;
	}
	void searchname(string word, bool& found, string& uid, string& foundlist)
	{
		string name = postcont;
		bool match = false;
		int counter = 0;
		for (int i = 0; i < name.size(); i++)
		{
			counter = 0;
			match = false;
			for (int j = 0; j < word.size(); j++)
			{
				if (name[i] == word[j])
				{
					i++;
					counter++;
					match = true;
					if (counter == word.size())
					{
						break;
					}
				}
				else
				{
					counter = 0;
					match = false;
				}
				if (j == word.size() - 1)
				{
					match = false;
				}
				if (i == name.size() - 1)
				{
					match = false;
					counter = 0;
					break;
				}
			}
			if (match == true)
			{
				break;
			}

		}
		if (match)
		{
			found = true;
			uid = postid;
			foundlist = name;
		}
	}
	~post()
	{
		if (sharedby != nullptr)
		{
			sharedby = nullptr;
		}
		if (likedby != nullptr)
		{
			delete[] likedby;
			likedby = nullptr;
			like_by = 0;
		}
	}
};

class socialmedia {
	int smusersize;
	user** smusers;
	int pagesize;
	pages** smpages;
	int smpostsize;
	post** smposts;
	int cmntsize;
	comments** smpostcmnts;

	int mainuserindex;
	string mainuserid, mainusername;

	date current;

public:
	socialmedia()
	{
		smusers = nullptr;
		smpages = nullptr;
		smpostcmnts = nullptr;
		smposts = nullptr;
		smusersize = 0;
		pagesize = 0;
		smpostsize = 0;
		cmntsize = 0;
	}

	void readalldata()
	{
		readdatausersm();
		readdatapages();
		readdataposts();
		readpostcomments();
		//cout << "All Data Read Successfully." << endl;
	}

	template<typename t>
	void extend(t*& arr, int size)
	{
		if (size > 0)
		{
			t* temp = new t[size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = new t[size + 1];
			for (int i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
		}
		else
		{
			arr = new t[size + 1];
		}
	}

	template<typename t>
	void extend(t**& arr, int size)
	{
		if (size > 0)
		{
			t** temp = new t * [size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = new t * [size + 1];
			for (int i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
		}
		else
		{
			arr = new t * [size + 1];
		}
	}

	void readdatausersm()
	{
		int length = 0;
		string str;
		ifstream fin("SocialNetworkUsers.txt");
		fin >> length;
		smusers = new user * [length];
		for (int i = 0; i < length; i++)
		{
			string userid;
			string firstname;
			string lastname;
			string** friendlist = nullptr;
			int friendcount = 0;
			pages** liked = nullptr;
			int likedpagescount = 0;

			fin >> userid;

			fin >> firstname;

			fin >> str;
			if (((str[0] >= 65 && str[0] <= 90) || (str[0] >= 97 && str[0] <= 122)) && ((str[1] >= 65 && str[1] <= 90) || (str[1] >= 97 && str[1] <= 122)))
			{
				lastname = str;
				fin >> str;
			}

			if (str[0] == 'u')
			{
				for (int z = 0; str != "-1"; z++)
				{
					extend(friendlist, friendcount);
					friendlist[z] = new string[3];

					friendlist[z][0] = str;
					friendcount++;
					fin >> str;
				}
				/*for (int z = 0; z < friendcount; z++)
				{
					cout << friendlist[z][0];
					cout << friendlist[z][1] << endl;
				}
				system("pause");*/
			}
			else
			{
				friendlist = nullptr;
			}

			fin >> str;

			if (str[0] == 'p')
			{
				for (int j = 0; str != "-1"; j++)
				{
					extend(liked, likedpagescount);
					liked[likedpagescount] = new pages[1];
					liked[likedpagescount++]->setid(str);
					fin >> str;
				}
			}
			smusers[i] = new user(userid, firstname, lastname, friendlist, friendcount, liked, likedpagescount);
			delete[] liked;
			delete[] friendlist;
			friendcount = 0;
			likedpagescount = 0;

			smusersize = i + 1;
		}
		fin.close();
	}

	void readdatapages()
	{
		int length = 0;
		string str;
		ifstream fin("SocialNetworkPages.txt");
		fin >> length;
		smpages = new pages * [length];
		for (int i = 0; i < length; i++)
		{
			string userid;
			string title;

			fin >> userid;

			getline(fin, title);

			if (title[0] == '\t')
			{
				for (int j = 0; j < title.size(); j++)
				{
					title[j] = title[j + 1];
				}
			}

			smpages[pagesize++] = new pages(userid, title);
		}
	}

	void readdataposts()
	{
		int length, activity, likedcount = 0;
		date shareddate;
		string date, postid, content, toa, sharedby, str, temp;

		ifstream fin("SocialNetworkPosts.txt");
		fin >> length;
		smposts = new post * [length];
		for (int i = 0; i < length; i++)
		{
			string* likedby = nullptr;
			fin >> postid;
			fin >> shareddate.day >> shareddate.month >> shareddate.year;
			fin.ignore();
			getline(fin, content);
			fin >> activity;
			if (activity > 0)
			{
				getline(fin, toa);
				if (toa[0] == ' ')
				{
					for (int s = 0; s < toa.size(); s++)
					{
						toa[s] = toa[s + 1];
					}
				}
			}
			fin >> sharedby;
			fin >> str;

			for (int j = 0; str != "-1"; j++)
			{
				extend(likedby, likedcount);
				likedcount++;
				likedby[j] = str;
				fin >> str;
				//cout << str;
			}
			if (str == "-1")
			{
				//getline(fin, str);
				fin >> temp;
				//cout <<temp;
			}
			extend(smposts, smpostsize);
			smposts[i] = new post(postid, shareddate, content, activity, toa, sharedby, likedby, likedcount);
			smpostsize++;
			delete[]likedby;
			likedcount = 0;

			//system("pause");
		}
	}

	void readpostcomments()
	{
		int length = 0;
		ifstream fin("SocialNetworkComments.txt");
		fin >> length;
		smpostcmnts = new comments * [length];
		for (int i = 0; i < length; i++)
		{
			string cid, pid, crid, cnt;
			fin >> cid >> pid >> crid;
			getline(fin, cnt);
			for (int j = 0; j < cnt.size(); j++)
			{
				if (cnt[j] == '\t')
				{
					for (int k = 0; k < cnt.size(); k++)
					{
						cnt[k] = cnt[k + 1];
					}
				}
				else
				{
					break;
				}
			}
			extend(smpostcmnts, cmntsize);
			smpostcmnts[cmntsize] = new comments(cid, pid, crid, cnt);
			cmntsize++;
		}
	}

	void finduser(string id) {
		for (int i = 0; i < smusersize; i++)
		{
			if (smusers[i]->findid(id))
			{
				smusers[i]->retname();
			}
		}
	}

	void setuser(string enteredid)
	{
		string name;
		for (int i = 0; i < smusersize; i++)
		{
			if (smusers[i]->findid(enteredid))
			{
				mainuserindex = i;
				mainuserid = enteredid;
				name = smusers[i]->retname();
			}
		}
		mainusername = name;
		cout << endl << name << " Successfully set as Current User. " << endl;
	}

	void getfriendlist()
	{
		int listsize = 0;
		string** friendlist = smusers[mainuserindex]->getfriendlist(listsize);

		for (int i = 0; i < listsize; i++)
		{
			cout << friendlist[i][0] << " - ";
			for (int j = 0; j < smusersize; j++)
			{
				if (smusers[j]->findid(friendlist[i][0]))
				{
					cout << " " << smusers[j]->retname();
					break;
				}
			}
			cout << endl;
		}

		friendlist = nullptr;
	}

	void viewlikedpages()
	{
		cout << mainusername << " - Liked Pages : \n\n";
		int pagesizespecific = 0;
		pages** pagelist = smusers[mainuserindex]->getlikedpages(pagesizespecific);
		for (int i = 0; i < pagesizespecific; i++)
		{
			string id = pagelist[i][0].getid();
			cout << id << " - ";
			for (int j = 0; j < pagesize; j++)
			{
				if (smpages[j][0].findid(id))
				{
					cout << smpages[j][0].returntitlebyid();
					break;
				}
			}
			cout << endl;
		}
		pagelist = nullptr;
	}

	void viewhome()
	{
		cout << mainusername << " - Home Page : " << endl << endl;
		int listsize = 0, pageslistsize = 0;
		string postid, Title;
		string** friendlist = smusers[mainuserindex]->getfriendlist(listsize);
		pages** pagelist = smusers[mainuserindex]->getlikedpages(pageslistsize);

		for (int i = 0; i < listsize; i++)
		{
			for (int j = 0; j < smusersize; j++)
			{
				if (smusers[j]->findid(friendlist[i][0]))
				{
					cout << " --- " << smusers[j]->retname();
					break;
				}
			}
			for (int k = 0; k < smpostsize; k++)
			{
				if (smposts[k]->findshareduser(friendlist[i][0]))
				{
					int likesize = 0;
					sm** likers = smposts[k]->printpost(postid, likesize);
					cout << endl << endl;
					cout << "Liked By : ";
					for (int m = 0; m < likesize; m++)
					{
						for (int j = 0; j < smusersize; j++)
						{
							if (smusers[j]->findid(likers[m][0].getid()))
							{
								cout << smusers[j]->retname();
								if (m != likesize - 1)
								{
									cout << " , ";
								}
								break;
							}
						}
					}
					if (likesize == 0)
					{
						cout << " None ";
					}
					cout << endl;

					for (int m = 0; m < cmntsize; m++)
					{
						if (smpostcmnts[m]->findid(postid))
						{
							string comment, commentby;
							smpostcmnts[m]->getcmnt(comment, commentby);
							for (int j = 0; j < smusersize; j++)
							{
								if (smusers[j]->findid(commentby))
								{
									cout << "\t" << smusers[j]->retname();
									break;
								}
							}
							cout << " Wrote \" " << comment << " \"" << endl;
						}
					}
					break;
				}
			}
			cout << endl;
		}
		//---------------------------------------------------------------------------------------------------------
		//For Page Comments
		for (int i = 0; i < pageslistsize; i++)
		{
			bool found = false;
			for (int j = 0; j < pagesize; j++)
			{
				if (smpages[j]->findid(pagelist[i][0].getid()))
				{
					Title = smpages[j]->retname();
					break;
				}
			}
			for (int k = 0; k < smpostsize; k++)
			{
				if (smposts[k]->findshareduser(pagelist[i][0].getid()))
				{
					int likesize = 0;
					cout << " --- " << Title << " ";
					sm** likers = smposts[k]->printpost(postid, likesize);
					cout << endl << endl;
					cout << "Liked By : ";
					for (int m = 0; m < likesize; m++)
					{
						for (int j = 0; j < smusersize; j++)
						{
							if (smusers[j]->findid(likers[m][0].getid()))
							{
								cout << smusers[j]->retname();
								if (m != likesize - 1)
								{
									cout << " , ";
								}
								break;
							}
						}
					}
					if (likesize == 0)
					{
						cout << " None " << endl;
					}
					cout << endl;
					for (int m = 0; m < cmntsize; m++)
					{
						if (smpostcmnts[m]->findid(postid))
						{
							string comment, commentby;
							smpostcmnts[m]->getcmnt(comment, commentby);
							for (int j = 0; j < smusersize; j++)
							{
								if (smusers[j]->findid(commentby))
								{
									cout << "\t" << smusers[j]->retname();
									found = true;
									break;
								}
							}
							for (int j = 0; j < pagesize; j++)
							{
								if (smpages[j]->findid(commentby))
								{
									cout << "\t" << smpages[j]->retname();
									found = true;
									break;
								}
							}
							cout << " Wrote \" " << comment << " \"" << endl;
						}
					}
					break;
				}
			}
			cout << endl;
		}

		friendlist = nullptr;
		pagelist = nullptr;
	}

	void likeapost(string pid)
	{
		int likesize = 0;
		bool found = false;

		for (int i = 0; i < smpostsize; i++)
		{
			if (smposts[i]->getpostid() == pid)
			{
				smposts[i]->likepost(mainuserid);
				found = true;
			}
		}
		if (!found)
		{
			cout << "Post ID Not Found.";
		}
	}

	void displaylikes(string pid)
	{
		cout << "Post Liked by : " << endl;
		int likesize = 0;
		for (int i = 0; i < smpostsize; i++)
		{
			if (smposts[i]->getpostid() == pid)
			{
				sm** likers = smposts[i]->fetchlikes(likesize);

				for (int m = 0; m < likesize; m++)
				{
					for (int j = 0; j < smusersize; j++)
					{
						if (smusers[j]->findid(likers[m][0].getid()))
						{
							cout << smusers[j]->getid() << "  -:-  " << smusers[j]->retname();
							if (m != likesize - 1)
							{
								cout << endl;
							}
							break;
						}
					}
					for (int j = 0; j < pagesize; j++)
					{
						if (smpages[j]->findid(likers[m][0].getid()))
						{
							cout << smpages[j]->getid() << "  -:-  " << smpages[j]->retname();
							if (m != likesize - 1)
							{
								cout << endl;
							}
							break;
						}
					}
				}
			}
		}
	}

	void printposts()
	{
		for (int i = 0; i < smpostsize; i++)
		{
			smposts[i]->print();
		}
	}

	void addcmnt(string pid, string cnt)
	{
		int index = 0;
		bool found = false;

		for (int i = 0; i < smpostsize; i++)
		{
			if (smposts[i]->getpostid() == pid)
			{
				found = true;
			}
		}
		if (found)
		{
			string cid = "c" + to_string(cmntsize + 1);

			for (int j = 0; j < cnt.size(); j++)
			{
				if (cnt[j] == '\t')
				{
					for (int k = 0; k < cnt.size(); k++)
					{
						cnt[k] = cnt[k + 1];
					}
				}
				else
				{
					break;
				}
			}
			extend(smpostcmnts, cmntsize);
			smpostcmnts[cmntsize] = new comments(cid, pid, mainuserid, cnt);
			cmntsize++;
		}
		else
		{
			cout << "Post Not Found." << endl;
		}
	}

	void displaypostwithcomments(string postid, int datesfn = 0)
	{
		sm** likers = nullptr;
		int likesize = 0;
		string title, sharer;
		bool foundsharer = false;
		//USER + POST Print
		for (int i = 0; i < cmntsize; i++)
		{
			if (smposts[i]->findid(postid))
			{
				sharer = smposts[i]->getshare();
				for (int m = 0; m < smusersize; m++)
				{
					if (smusers[m]->getid() == sharer)
					{
						title = smusers[m]->retname();
						foundsharer = true;
					}
				}
				if (!foundsharer)
				{
					for (int m = 0; m < pagesize; m++)
					{
						if (smpages[m]->getid() == sharer)
						{
							title = smpages[m]->retname();
							foundsharer = true;
						}
					}
				}
				cout << title;
				likers = smposts[i]->printpost(postid, likesize);
				if (datesfn == 1)
				{
					cout << "..." << smposts[i]->getdate();
				}
				break;
			}
		}
		//LIKE Print
		cout << endl << "Liked By : ";
		for (int m = 0; m < likesize; m++)
		{
			for (int j = 0; j < smusersize; j++)
			{
				if (smusers[j]->findid(likers[m][0].getid()))
				{
					cout << smusers[j]->retname();
					if (m != likesize - 1)
					{
						cout << " , ";
					}
					break;
				}
			}
			for (int j = 0; j < pagesize; j++)
			{
				if (smpages[j]->findid(likers[m][0].getid()))
				{
					cout << smpages[j]->retname();
					if (m != likesize - 1)
					{
						cout << " , ";
					}
					break;
				}
			}
		}

		if (likesize == 0)
		{
			cout << " None ";
		}
		bool found = false;
		cout << endl;
		for (int m = 0; m < cmntsize; m++)
		{
			if (smpostcmnts[m]->findid(postid))
			{
				string comment, commentby;
				smpostcmnts[m]->getcmnt(comment, commentby);
				cout << "\t";

				for (int j = 0; j < smusersize; j++)
				{
					if (smusers[j]->findid(commentby))
					{
						cout << smusers[j]->retname();
						found = true;
						break;
					}
				}
				for (int j = 0; j < pagesize; j++)
				{
					if (smpages[j]->findid(commentby))
					{
						cout << smpages[j]->retname();
						found = true;
						break;
					}
				}
				cout << " Wrote \" " << comment << " \"" << endl;
			}
		}
		cout << endl;
	}

	void viewtimeline()
	{
		string username = smusers[mainuserindex]->retname(), postid;
		int likesize = 0;
		sm** likers = nullptr;
		for (int i = 0; i < smpostsize; i++)
		{
			if (smposts[i]->getshare() == mainuserid)
			{

				cout << endl << " --- " << username << "  ";
				likers = smposts[i]->printpost(postid, likesize);
				cout << "..." << smposts[i]->getdate();
				cout << endl << endl;
				cout << "Liked By : ";
				for (int m = 0; m < likesize; m++)
				{
					for (int j = 0; j < smusersize; j++)
					{
						if (smusers[j]->findid(likers[m][0].getid()))
						{
							cout << smusers[j]->retname();
							if (m != likesize - 1)
							{
								cout << " , ";
							}
							break;
						}
					}
					for (int j = 0; j < pagesize; j++)
					{
						if (smpages[j]->findid(likers[m][0].getid()))
						{
							cout << smpages[j]->retname();
							if (m != likesize - 1)
							{
								cout << " , ";
							}
							break;
						}
					}
				}
				if (likesize == 0)
				{
					cout << " None ";
				}
				bool found = false;
				for (int m = 0; m < cmntsize; m++)
				{
					if (smpostcmnts[m]->findid(postid))
					{
						cout << endl;
						string comment, commentby;
						smpostcmnts[m]->getcmnt(comment, commentby);
						for (int j = 0; j < smusersize; j++)
						{
							if (smusers[j]->findid(commentby))
							{
								cout << "\t" << smusers[j]->retname();
								found = true;
								break;
							}
						}
						for (int j = 0; j < pagesize; j++)
						{
							if (smpages[j]->findid(commentby))
							{
								cout << "\t" << smpages[j]->retname();
								found = true;
								break;
							}
						}
						cout << " Wrote \" " << comment << " \"" << endl;
					}
				}
			}
		}

	}

	void viewpage(string pageid)
	{
		int index;
		string title;
		for (int i = 0; i < pagesize; i++)
		{
			if (smpages[i]->findid(pageid))
			{
				index = i;
				title = smpages[i]->retname();
			}
		}
		string  postid;
		int likesize = 0;
		sm** likers = nullptr;
		for (int i = 0; i < smpostsize; i++)
		{
			if (smposts[i]->getshare() == pageid)
			{
				cout << " ---" << title;
				likers = smposts[i]->printpost(postid, likesize);
				cout << endl << "Liked By : ";
				for (int m = 0; m < likesize; m++)
				{
					for (int j = 0; j < smusersize; j++)
					{
						if (smusers[j]->findid(likers[m][0].getid()))
						{
							cout << smusers[j]->retname();
							if (m != likesize - 1)
							{
								cout << " , ";
							}
							break;
						}
					}
					for (int j = 0; j < pagesize; j++)
					{
						if (smpages[j]->findid(likers[m][0].getid()))
						{
							cout << smpages[j]->retname();
							if (m != likesize - 1)
							{
								cout << " , ";
							}
							break;
						}
					}
				}
				if (likesize == 0)
				{
					cout << " None " << endl;
				}
				bool found = false;
				cout << endl << endl;
				for (int m = 0; m < cmntsize; m++)
				{
					if (smpostcmnts[m]->findid(postid))
					{
						string comment, commentby;
						smpostcmnts[m]->getcmnt(comment, commentby);
						cout << "\t";
						for (int j = 0; j < smusersize; j++)
						{
							if (smusers[j]->findid(commentby))
							{
								cout << smusers[j]->retname();
								found = true;
								break;
							}
						}
						for (int j = 0; j < pagesize; j++)
						{
							if (smpages[j]->findid(commentby))
							{
								cout << smpages[j]->retname();
								found = true;
								break;
							}
						}
						cout << " Wrote \" " << comment << " \"" << endl;
					}
				}
				cout << endl;
			}
		}

	}

	void setsysdate(int dy, int mn, int yr)
	{
		current.day = dy;
		current.month = mn;
		current.year = yr;

		cout << "Date Set as ";
		cout << current.day << " / " << current.month << " / " << current.year << endl;
	}

	void sharepost(string pid)
	{
		string postid, content, sharedby = mainuserid, toa;
		int  activity = 0;
		date shareddate;
		string title;
		bool found = false;
		shareddate = current;
		for (int i = 0; i < smpostsize; i++)
		{
			if (smposts[i]->findid(pid))
			{
				title = smposts[i]->getshare();
				content = smposts[i]->getcnt();
				activity = smposts[i]->getact();
				toa = smposts[i]->gettoa();
			}
		}
		for (int i = 0; i < smusersize; i++)
		{
			if (smusers[i]->getid() == title)
			{
				title = smusers[i]->retname();
				found = true;
			}
		}
		if (!found)
		{
			for (int i = 0; i < pagesize; i++)
			{
				if (smpages[i]->getid() == title)
				{
					title = smpages[i]->retname();
					found = true;
				}
			}
		}

		switch (activity)
		{
		case 0:
			content = "\n" + title + " Shared  " + "  " + content;
			break;
		case 1:
			content = "\n" + title + " is feeling " + toa + "  " + content;
			break;
		case 2:
			content = "\n" + title + " is thinking about " + toa + "  " + content;
			break;
		case 3:
			content = "\n" + title + " is making " + toa + "  " + content;
			break;
		case 4:
			content = "\n" + title + " is Celebrating " + toa + "  " + content;

			break;
		}


		extend(smposts, smpostsize);
		smposts[smpostsize] = new post(postid, shareddate, content, 0, " ", sharedby, nullptr, 0);

		smpostsize++;

	}

	void search(string word)
	{
		string id, foundlist;
		bool found = false;
		date shared;
		cout << "Users : " << endl;
		for (int i = 0; i < smusersize; i++)
		{
			smusers[i]->searchname(word, found, id, foundlist);
			if (found)
			{
				cout << " ---" << id << " -:- " << foundlist << endl;
				found = false;
			}
		}

		cout << "Posts : " << endl;
		for (int i = 0; i < smpostsize; i++)
		{
			smposts[i]->searchname(word, found, id, foundlist);
			if (found)
			{
				cout << " ---" << id << " - ";
				for (int z = 0; z < smpostsize; z++)
				{
					if (smposts[z]->findid(id))
					{
						string uid = smposts[z]->getshare();
						string name;
						for (int k = 0; k < smusersize; k++)
						{
							if (smusers[k]->getid() == uid)
							{
								name = smusers[k]->retname();
								break;
							}
						}
						cout << name << "  ";
						smposts[z]->printpostwol(shared);
						cout << "..." << shared.day << "/" << shared.month << "/" << shared.year << endl;
					}
				}
				found = false;
			}
		}
		cout << "Pages : " << endl;
		for (int i = 0; i < pagesize; i++)
		{
			smpages[i]->searchname(word, found, id, foundlist);
			if (found)
			{
				cout << " ---" << id << " -:- " << foundlist << endl;
				found = false;
			}
		}
	}
	void RunApp()
	{
		cout << "Command : Set Current User  as u7.";
		//cout << "Kindly Enter Your ID : ";
		//cin >> enteredid;
		setuser("u7");
		cout << endl << "Command: Set current System Date 15/11/2017" << endl;
		setsysdate(15, 11, 2017);

		cout << endl << "Command: View Friend List" << endl;
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		cout << endl << mainusername << " - Friend List : " << endl << endl;
		getfriendlist();

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl << "Comand: View Liked Pages" << endl;
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		viewlikedpages();

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: View Home : ";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		viewhome();

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: View TimeLine : ";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		cout << mainusername << " -- TimeLine : " << endl;
		viewtimeline();


		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: ViewLikedList(post5)";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		displaylikes("post5");

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: LikePost(post5) " << endl;
		cout << "Command: ViewLikedList(post5)";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		likeapost("post5");
		displaylikes("post5");

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: PostComment(post4, Good Luck for your Result) " << endl;
		cout << "Command: ViewPost(post4)";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		addcmnt("post4", "Good Luck for your Result");
		displaypostwithcomments("post4");

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: PostComment(post8, Thanks for the wishes) " << endl;
		cout << "Command: ViewPost(post8)";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		addcmnt("post8", "Thanks for the wishes");
		displaypostwithcomments("post8", 1);

		cout << endl << "----------------------------------------------------------------------------------------------" << endl;

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: SharePost(post5)" << endl;
		cout << "Command: View TimeLine ";
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		sharepost("post5");
		viewtimeline();

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: ViewPage(p1)" << endl;
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;

		viewpage("p1");

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: Search Ali" << endl;
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		search("Ali");

		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Command: Search Birthday" << endl;
		cout << endl << "-------------------------------------------------------------------------------------------------------------" << endl;
		search("Birthday");
	}

	void printdata()
	{
		for (int i = 0; i < smusersize; i++)
		{
			smusers[i]->print();
			cout << endl;
		}
		cout << endl << "----------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < pagesize; i++)
		{
			smpages[i]->print();
			cout << endl;
		}
		cout << endl << "----------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < smpostsize; i++)
		{
			smposts[i]->print();
			cout << endl;
		}
		cout << endl << "----------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < cmntsize; i++)
		{
			smpostcmnts[i]->print();
			cout << endl;
		}

	}

	~socialmedia()
	{
		if (smusers != nullptr)
		{
			for (int i = 0; i < smusersize; i++)
			{
				delete smusers[i];
			}
			delete[] smusers;
			smusers = nullptr;
			smusersize = 0;
		}

		if (smpages != nullptr)
		{

			for (int i = 0; i < pagesize; i++)
			{
				delete smpages[i];
			}
			delete[] smpages;
			smpages = nullptr;
			pagesize = 0;
		}

		if (smposts != nullptr)
		{
			for (int i = 0; i < smpostsize; i++)
			{
				delete smposts[i];
			}

			delete[] smposts;
			smposts = nullptr;
			smpostsize = 0;
		}

		if (smpostcmnts != nullptr)
		{
			for (int i = 0; i < cmntsize; i++)
			{
				delete smpostcmnts[i];
			}
			delete[] smpostcmnts;
			smpostcmnts = nullptr;
			cmntsize = 0;
		}
	}
};

int main()
{
	socialmedia fastbook;
	fastbook.readalldata();
	fastbook.RunApp();

	cout << endl;
	cout << "NOTE :: While Adding Comment Good Luck for your Result in Post 4 . It's Allready in the Data File.So It will show duplication.";
	// NOTE :: While Adding Comment Good Luck for your Result in Post 4 . It's Allready in the Data File.So It will show duplication.
}