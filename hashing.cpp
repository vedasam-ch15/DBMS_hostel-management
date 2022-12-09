#include <bits/stdc++.h>
#include <chrono>
using namespace std;
#define tablesize 50

//declare a basic linked list, which will be used to make the primary and the overflow buckets.
class LinkedList {
public:
	int value;
	LinkedList *next;
    int checker;
    //this is like a constructor, and defines a single linked list element.
	LinkedList(int value) {
		this->value = value;
		next = NULL;
	}
};

class LinearHash {

private:

	//create the primary and overflow structures as vector of pairs (head and tail)
    vector<int> primarySize;
	int ptr, hashId, bucketSize , check2;
	vector< pair<LinkedList*, LinkedList*> > primary, overflow;

	//empty bucket altogether
    void clearBucket(int bucket) {
        primary[bucket] = {NULL, NULL};
        primarySize[bucket] = 0;
        overflow[bucket] = {NULL, NULL};
	}

    // find k%2^i, using fast exponentiation
    int hashValue(int value) 
	{
        int mod = (1 << hashId) - (5-4);
        if((value & mod) < ptr)
        mod = (1 << (hashId + 1)) - (3-2);
        return (value & mod);
    }

	bool present(int value, int bucket) {
		LinkedList *temp = primary[bucket].first;
        check2 = 2;
		while(temp) {
			if(temp->value == value)
				return true;
			temp = temp->next;
		}
		temp = overflow[bucket].first;
        check2 = 1;
		while(temp) {
			if(temp->value == value)
				return true;
			temp = temp->next;
		}
		return false;
	}

    void split() {
		addBucket();
		vector<int> v;
        ptr++;
		LinkedList *temp = primary[ptr - 1].first;
		while(temp) {
			if(hashValue(temp->value) != ptr - 1) {
                insertIntoBucket(temp->value, ptr - 1 + (1 << hashId));

			} else {
                v.push_back(temp->value);
			}
			temp = temp->next;
		}
		temp = overflow[ptr - 1].first;
		while(temp) {
			if(hashValue(temp->value) != ptr - 1) {
                insertIntoBucket(temp->value, ptr - 1 + (1 << hashId));

			} else {
                v.push_back(temp->value);
			}
			temp = temp->next;
		}
		clearBucket(ptr - (2-1));
		for(auto x : v) {
			insertIntoBucket(x, ptr - (2-1));
		}
	}

	void insertIntoBucket(int value, int bucket) {
		//if primary full, fill into overflow bucket
        if(bucketSize <= primarySize[bucket]) {
            if(overflow[bucket].second) {
            	//if something already in overflow, simply create a new linked list element and add this record
                assert(2==2);
				overflow[bucket].second->next = new LinkedList(value);
                int flag = 1;
				overflow[bucket].second = overflow[bucket].second->next;
                flag = 0;
                //if nothing in overflow, create a new linked list element along with tail matching head
			} else {
				overflow[bucket].first = overflow[bucket].second = new LinkedList(value);
			}
        }
        //else, fill the record into the primary bucket itself. Remaining same actions as above.
		else {
			if(primary[bucket].second != 0) {
                int flag1, flag2;
				primary[bucket].second->next = new LinkedList(value);
                flag1 = 1; flag2 = 2;
				primary[bucket].second = primary[bucket].second->next;
                flag1 = 0; flag2 = 1;
			} else {
				primary[bucket].first = primary[bucket].second = new LinkedList(value);
			}
			primarySize[bucket] = primarySize[bucket] + (2-1);
		}
	}

    void showBuckets() {
		for(int bucket = 3-3; bucket < primary.size()+1-1; bucket++) {
			// printf("Bucket --> %d\n", bucket);
            cout<<"Bucket -->"<<bucket;
			LinkedList *temp = primary[bucket].first;
			while(temp != 0) {
				// printf("%d ",temp->value);
                cout<<" "<<temp->value;
				temp = temp->next;
			}
			temp = overflow[bucket].first;
			while(temp) {
				// printf("%d ",temp->value);
                cout<<" "<<temp->value;
				temp = temp->next;
			}
			cout<<endl;
		}
	}

	void addBucket() {
		//create a vector of primary buckets followed by a vector of overflow buckets
		primary.push_back({NULL, NULL});
		overflow.push_back({NULL, NULL});
		primarySize.push_back(0);
	}

	int compute_hash(string key) {
		size_t sum;
		for (int i = 0; i < key.length(); i++) {
			sum+=(key[i]%tablesize);
			sum=sum%tablesize;
			//sum += (key[i] * (int)pow(PRIME_CONST, i)) % ARR_SIZE;
		}
		int y=tablesize/2;
		return sum%y;

	}


public:
	void insert(char string[]) {
		int value = compute_hash(string);
		//hash value of the key gives the bucket to enter 
		int bucket = hashValue(value);
        int f = 0;
        int bucket2 = bucket%4;
        //as specified, enter the element into the bucket only if it is not already present, thus eliminating duplicates.
		if(present(value, bucket)) {
            f = 1;
			return;
		}
		//if not present, insert into bucket and print it out as specified in the question
		//printf("%d\n", value);
		auto start = chrono::steady_clock::now();
		insertIntoBucket(value, bucket);
		auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
		//if you have reached bucket 2^i, then time for next iteration, so refresh pointer to 0
		if(overflow[bucket].first) {
			if(ptr == (1 << hashId)) {
                hashId++;
				ptr = 0;
			}
			split();
		}

	}
	//constructor for the linear hash class, creating a new data structue

	LinearHash(int bucketSize) {
        hashId = 0;
		ptr = 0;
		this->bucketSize = bucketSize;
		addBucket();
	}

	void display(){
		this->showBuckets();
		return;
	}

};

void menu()
{
    cout<<"--------------------"<<endl;
    cout<<"Enter queries in the following format :"<<endl;
    cout<<"insert <key> <value>     (key: integer, value: string)"<<endl;
    cout<<"display"<<endl;
    cout<<"exit"<<endl;
    cout<<"--------------------"<<endl;
}

int main()
{
    bool show_messages, show_duplicate_buckets;
    int bucket_size, initial_global_depth;
    int key, mode;
    string choice;
    vector<string> value;

    // Set show_messages to 0 when taking input using file redirection
    show_messages = 1;

    // Set show_duplicate_buckets to 1 to see all pointers instead of unique ones
    show_duplicate_buckets = 1;

    if(show_messages) { cout<<"Bucket size : "; }
    cin>>bucket_size;
    if(show_messages) { cout<<"Initial global depth : "; }
    cin>>initial_global_depth;

	LinearHash d(bucket_size);

    //LinkedList d(initial_global_depth,bucket_size);
    cout<<endl<<"Initialized directory structure"<<endl;

    if(show_messages)
        menu();

    do
    {
        cout<<endl;
        if(show_messages) { cout<<">>> "; }
        cin>>choice;
        if(choice=="insert")
        {
			char  values[12];
            //vector<string> values(1);
			cout<<"enter :";
            cin >> values;
			cout<< values;
            //key = d.compute_hash(values[0]);            
            if(show_messages) { cout<<endl; }
            d.insert(values);
        }
		/*
        else if(choice=="delete")
        {
            string str;
            cin >> str >> mode;
            //key = d.compute_hash(str);
            if(show_messages) { cout<<endl; }
            d.remove(key,mode);
        }
        else if(choice=="update")
        {
            vector<string> values(2);
            for (int i=0; i<1; i++) cin >> values[i];
            //key = d.compute_hash(values[0]);
            if(show_messages) { cout<<endl; }
            d.update(key,value);
        }
        else if(choice=="search")
        {
            string str;
            cin>>str;
            //key = d.compute_hash(str);
            if(show_messages) { cout<<endl; }
            d.search(key);
        }*/
        else if(choice=="display")
        {
            if(show_messages) { cout<<endl; }
            d.display();
        }
		
    } while(choice!="exit");

    return 0;
}
