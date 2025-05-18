#include "main.h"
int MAXSIZE = 0;
const int NUMBER_OF_ROTATIONS = 3;

struct Node 
{
	char data;
	int frequency;
	Node * left;
	Node * right;

	Node (char d, int freq) : 
		data (d), frequency (freq), left (nullptr), right (nullptr) {}
	~Node () {}

	void print () 
	{
		cout << data << ": " << frequency << endl;
	}
};

struct HeapNode 
{
	int label;
	int order;
	deque<int> customers;

	HeapNode (int label, int order) : label (label), order (order) {}
	~HeapNode () {}

	void print () 
	{
		cout << label << ": " << order << " [ ";
		if (!customers.empty()) 
			for (int customer : customers)
				cout << customer << " ";
		cout << "]" << endl;
	}

	bool operator > (const HeapNode & rhs) const 
	{
		if (customers.size() != rhs.customers.size())
			return customers.size() > rhs.customers.size();
		else return order > rhs.order;
	}
};

struct Compares 
{
	bool operator () (const pair <Node * , int> & left, const pair<Node *, int> & right) 
	{
		// Sort by frequency in descending order
		if (left.first->frequency != right.first->frequency)
			return left.first->frequency > right.first->frequency;
		// If frequencies are equal, sort alphabetically in ascending order
		else
		{
			if(left.first->data == '-' && right.first->data == '-')
				return left.second > right.second;
			else if ((isupper (left.first->data) && isupper (right.first->data)) || 
					 (islower (left.first->data) && islower (right.first->data)))
					return left.first->data > right.first->data;
			else return left.first->data < right.first->data;
		}
	}

	bool operator () (const pair<int, char> & a, const pair<int, char> & b) 
	{
		if (a.first != b.first)
			return a.first > b.first;
		else if ((isupper (a.second) && isupper (b.second)) || 
				 (islower (a.second) && islower (b.second)))
					return a.second > b.second;
		else return a.second < b.second;
	}

	bool operator () (HeapNode * const & a1, HeapNode * const & a2) 
	{
		if (a1->customers.size() == a2->customers.size())
			return a1->order < a2->order;
		return a1->customers.size() < a2->customers.size();
	}
};

// region[rgba(0, 200, 100, 0.3)]
class Tree
{
	protected:
		void printTreeHelper (Node * root, string prefix = "", bool isLeft = true)
		{
			if (root)
			{
				cout << prefix <<  "|___ H" << getHeight(root) << ". ";
				root->print();
				printTreeHelper (root->right, prefix + (isLeft ? "|    " : "     "), true);
				printTreeHelper (root->left, prefix + (isLeft ? "|    " : "     "), false);
			}
		}

		bool searchHelper (Node * root, char data, int & frequency)
		{
			if (!root) return false;

			if (root->data == data)
			{
				frequency = root->frequency;
				return true;
			}

			if (searchHelper (root->left, data, frequency))
				return true;
			if (searchHelper (root->right, data, frequency))
				return true;

			return false;
		}

		void clearHelper (Node * root) 
		{
			if (root) 
			{
				clearHelper(root->left);
				clearHelper(root->right);
				delete root;
			}
		}

		int getSize (Node * node)
		{
			if (!node) return 0;
			return getSize (node->left) + getSize (node->right) + 1;
		}

		int getHeight (Node * node)
		{
			if (!node) return 0;
			return max (getHeight (node->left), getHeight (node->right)) + 1;
		}

		// Utility functions for AVL Tree rebalancing
		int getBalanceFactor (Node * node)
		{
			if (!node) return 0;
			return getHeight (node->left) - getHeight (node->right);
		}

		Node * rightRotate (Node * root) 
		{
			Node * newRoot = root->left;
			root->left = newRoot->right;
			newRoot->right = root;
			return newRoot;
		}

		Node * leftRotate (Node * root) 
		{
			Node * newRoot = root->right;
			root->right = newRoot->left;
			newRoot->left = root;
			return newRoot;
		}

		Node * rebalance (Node * node, bool & success)
		{
			if (!node || success) return node;
			int balance = getBalanceFactor (node);

			// Left Heavy
			if (balance > 1) 
			{
				success = true;
				// Left-Right Case
				if (getBalanceFactor (node->left) < 0)
					node->left = leftRotate (node->left);
				// Left-Left Case
				return rightRotate (node);
			}
			// Right Heavy
			else if (balance < -1) 
			{
				success = true;
				// Right-Left Case
				if (getBalanceFactor (node->right) > 0)
					node->right = rightRotate (node->right);
				// Right-Right Case
				return leftRotate(node);
			}

			return node;
		}

		// Traversal functions
		template <typename T>
		void preorderTraversal (Node * node, vector<T> & v)
		{
			if (!node) return;

			v.push_back (node->frequency);

			preorderTraversal (node->left, v);
			preorderTraversal (node->right, v);
		}

		template <typename T>
		void inorderTraversal (Node * node, vector<T> & v)
		{
			if (!node) return;
			inorderTraversal (node->left, v);

			string s = "";
			if (node->data != '-')
				s += node->data;
			else s += to_string (node->frequency);
			v.push_back (s);

			inorderTraversal (node->right, v);
		}

		template <typename T>
		void postorderTraversal (Node * node, vector<T> & v)
		{
			if (!node) return;

			postorderTraversal (node->left, v);
			postorderTraversal (node->right, v);

			v.push_back (node->frequency);
		}
};
// endregion

// region[rgba(0, 255, 200, 0.3)]
class HuffmanAVLTree : public Tree
{
	Node * root;

	// Private utility functions for Huffman Tree construction
	Node * buildHuffmanTree(vector< pair<int, char> > &v)
	{
		priority_queue<pair<Node *, int>, vector< pair<Node *, int> >, Compares> pq;
		int insertionOrder = 0;

		// Create leaves for each character and add them to the priority queue
		for (const auto & entry : v)
		{
			Node * leaf = new Node (entry.second, entry.first);
			pq.push ({leaf, insertionOrder});
		}

		// Build Huffman Tree
		while (pq.size() > 1)
		{
			pair<Node *, int> left = pq.top();
			pq.pop();
			pair<Node *, int> right = pq.top();
			pq.pop();

			Node * internalNode = new Node ('-', left.first->frequency + right.first->frequency);
			internalNode->left = left.first;
			internalNode->right = right.first;

			// Rebalance the tree
			for (int i = 0; i < NUMBER_OF_ROTATIONS; i++)
			{
				bool success = false;
				internalNode = huffmanRebalance (internalNode, success);
			}

			pq.push ({internalNode, ++insertionOrder});
		}
		// The top of the priority queue is the root of the Huffman Tree
		return pq.top().first;
	}

	Node * huffmanRebalance (Node * node, bool & success)
	{
		if (!node) return node;
		
		node = rebalance (node, success);
		node->left = huffmanRebalance (node->left, success);
		node->right = huffmanRebalance (node->right, success);

		return node;
	}

	string encodedBinaryStringHelper (Node * root, char c, string currentPath)
	{
		if (!root) return "";

		// If the character is found, return the binary string
		if (root->data == c) return currentPath;

		// Recursively search the left and right subtrees
		string left = encodedBinaryStringHelper (root->left, c, currentPath + "0");
		string right = encodedBinaryStringHelper (root->right, c, currentPath + "1");

		// Return the non-empty result (either from left or right subtree)
		return (left != "") ? left : right;
	}

	public:
		HuffmanAVLTree() : root (nullptr) {}
		~HuffmanAVLTree() { clearHelper (root); }

		pair<char, int> getPair () 
		{
			return make_pair (root->data, root->frequency);
		}
		// Public function to build Huffman Tree
		void build (vector< pair<int, char> > & v)
		{
			root = buildHuffmanTree (v);
		}

		// Public funtion to find the encoded binary string of a character
		string encodedBinaryString (char c)
		{
			return encodedBinaryStringHelper (root, c, "");
		}

		void storeDeque (deque< vector<string> > & HAND_customers)
		{
			vector<string> v;
			inorderTraversal (root, v);
			HAND_customers.push_back (v);
		}

		// // Public function to print Huffman tree
		void print() 
		{
			cout << "Huffman Tree:" << endl;
			printTreeHelper (root);
		}
};
// endregion

// region[rgba(100, 255, 100, 0.3)]
class BinarySearchTree : public Tree
{
	Node * root;

	Node * insertHelper (Node * root, char data, int frequency) 
	{
        if (!root) return new Node (data, frequency);

        if (frequency < root->frequency)
            root->left = insertHelper (root->left, data, frequency);
        else root->right = insertHelper (root->right, data, frequency);

        return root;
    }

    Node * removeHelper (Node * root, int data) 
	{
        if (!root) return root;

        if (data < root->frequency)
            root->left = removeHelper (root->left, data);
        else if (data > root->frequency)
            root->right = removeHelper (root->right, data);
        else 
		{
            // Node with only one child or no child
            if (!root->left) 
			{
                Node * temp = root->right;
                delete root;
                return temp;
            } 
			else if (!root->right) 
			{
                Node * temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children, get the inorder successor
            Node * temp = findMin (root->right);
            // Copy the inorder successor's content to this node
            root->data = temp->data;
            root->frequency = temp->frequency;
            // Delete the inorder successor
            root->right = removeHelper (root->right, temp->data);
        }
        return root;
    }

    Node * findMin (Node * node) 
	{
        while (node->left)
            node = node->left;
        return node;
    }

	public:
		BinarySearchTree () : root (nullptr) {}
		~BinarySearchTree () { clear(); }

		Node * getRoot () 
		{
			return root;
		}

		bool search (char data, int & frequency) 
		{
			return searchHelper (root, data, frequency);
		}

		int size ()
		{
			return getSize (root);
		}

		void insert (char order, int frequency) 
		{
			root = insertHelper (root, '-', frequency);
		}

		void remove (int data) 
		{
			root = removeHelper (root, data);
		}

		void BSTpreorderTraversal (Node * node, vector<int> & v)
		{
			preorderTraversal (node, v);
		}

		void BSTinorderTraversal (Node * node, vector<string> & v)
		{
			inorderTraversal (node, v);
		}

		void BSTpostorderTraversal (Node * node, vector<int> & v)
		{
			postorderTraversal (node, v);
		}

		void clear() 
		{
			clearHelper(root);
			root = nullptr;
		}

		void print() 
		{
			cout << "Binary Search Tree:" << endl;
			printTreeHelper (root);
		}
};
// endregion

// region[rgba(255, 255, 100, 0.3)]
class Heap : public Tree
{
	vector<HeapNode *> heap;

	public:
		Heap () {}
		~Heap () 
		{
			for (HeapNode * node : heap)
				delete node;
		}

		vector<HeapNode *> getHeap () 
		{
			return heap;
		}

		queue<HeapNode *> getAreaToRM (int num) 
		{
			queue<HeapNode *> q;
			if (num > (int) heap.size()) num = heap.size();

			vector<HeapNode *> temp = heap;
			
			sort (temp.begin(), temp.end(), Compares());
			for (int i = 0; i < num; i++)
				q.push (temp[i]);
			
			return q;
		}

		HeapNode * top () 
		{
			return heap[0];
		}

		void pop () 
		{
			HeapNode * temp = heap[0];

			heap[0] = heap[heap.size() - 1];
			heap.pop_back();
			heapifyDown (0);

			delete temp;
		}

		int size () 
		{
			return heap.size();
		}

		void insert (HeapNode node, int data) 
		{
			HeapNode * newNode = new HeapNode (node.label, node.order);

			bool found = false;
			int index = 0;
			int size = heap.size();

			for (int i = 0; i < size; i++)
			{
				if (heap[i]->label == newNode->label)
				{
					heap[i]->order = newNode->order;
					heap[i]->customers.push_back (data);

					found = true;
					index = i;
					break;
				}
			}

			if (!found)
			{
				newNode->customers.push_back (data);
				heap.push_back (newNode);
				index = size;
				heapifyUp (index);
			}
			else delete newNode;

			heapifyDown (index);
		}

		void heapifyUp (int index) 
		{
			if (!index) return;

			int parentIndex = (index - 1) / 2;
			if (*heap[parentIndex] > *heap[index])
			{
				swap (heap[parentIndex], heap[index]);
				heapifyUp (parentIndex);
			}
		}

		void heapifyDown (int index) 
		{
			int leftChildIndex = 2 * index + 1;
			int rightChildIndex = 2 * index + 2;

			if (leftChildIndex >= (int) heap.size()) return;

			int minIndex = index;
			if (*heap[minIndex] > *heap[leftChildIndex])
				minIndex = leftChildIndex;
			if (rightChildIndex < (int) heap.size() && *heap[minIndex] > *heap[rightChildIndex])
				minIndex = rightChildIndex;

			if (minIndex != index)
			{
				swap (heap[index], heap[minIndex]);
				heapifyDown (minIndex);
			}
		}

		HeapNode getMin () 
		{
			return *heap[0];
		}

		void remove (int label) 
		{
			int index = -1;
			for (unsigned int i = 0; i < heap.size(); ++i)
			{
				if (heap[i]->label == label)
				{
					index = i;
					break;
				}
			}
			if (index == -1) return;

			HeapNode * temp = heap[index];

			heap[index] = heap[heap.size() - 1];
			heap.pop_back();

			heapifyDown (index);

			delete temp;
		}

		void removeEmpty () 
		{
			for (unsigned int i = 0; i < heap.size(); ++i)
			{
				if (heap[i]->customers.empty())
				{
					HeapNode * temp = heap[i];

					heap[i] = heap[heap.size() - 1];
					heap.pop_back();
					heapifyDown (i);

					delete temp;
				}
			}
		}

		void print () 
		{
			cout << "Heap:" << endl;
			for (HeapNode * node : heap)
				node->print();
		}
};
// endregion

// region[rgba(100, 100, 255, 0.4)]
class Restaurant
{
	public:
		map<int, BinarySearchTree> hashMap;
		Heap minheap;

	private:
    int size;
    int maxsize;
	int heapcount = 0;
	int bstcount = 0;

	bool isGojosRestaurant (int result) 
	{
		return result & 1;
	}

	// Assign to the BST in the hash table for Gojo's restaurant
	void assignAreaGojos (int result, int areaID) 
	{
		hashMap[areaID].insert (bstcount++, result);
	}

	// Assign to the min-heap for Sukuna's restaurant
	void assignAreaSukuna (int result, int areaID) 
	{
		HeapNode node (areaID, heapcount++);

		minheap.insert (node, result);
		if (minheap.size() > maxsize)
			minheap.remove (minheap.getMin().label);
	}

	public:
		Restaurant () : size (0), maxsize (0) {}
		~Restaurant () {}

		Restaurant (int maxsize) : maxsize (maxsize) {}

		int getsize () 
		{
			return size;
		}

		void setMaxSize (int maxsize) 
		{
			this->maxsize = maxsize;
		}

		void assignArea (int result) 
		{
			int areaID = (result % MAXSIZE) + 1;
			if (isGojosRestaurant (result))
				assignAreaGojos (result, areaID);
			else assignAreaSukuna (result, areaID);
			size++;
    	}

		void print () 
		{
			cout << "Gojo's Restaurant: " << endl;
			for (auto & entry : hashMap)
			{
				cout << entry.first << ": ";
				entry.second.print();
			}

			cout << "Sukuna's Restaurant:" << endl;
			for (auto & entry : minheap.getHeap())
				entry->print();
		}
};
// endregion

// region[rgba(255, 100, 255, 0.3)]
class Operations
{
	deque< vector<string> > HAND_customers;
	deque< vector<string> > LIMITLESS_customers;
	deque< vector<string> > CLEAVE_customers;

	public:
		Restaurant Restaurants;
		Operations () {}
		~Operations () {}

//========================== LAPSE ==============================//
		void LAPSE (string customerName)
		{
			if (customerName.empty()) return;

			int result = 0;
			string resultBinaryString = "";
			HuffmanAVLTree huffmanAVLTree;

			map<char, int> charFreq;
			vector< pair<int, char> > charsVector;
			vector< pair<int, char> > shiftedChars;

			// Count the frequency of each character
			for (char c : customerName)
			{
				if (isalpha(c)) charFreq[c]++;
				else return;
			}
			if (charFreq.size() < 3) return;

			// Emply the map into a vector of pairs
			for (const auto & entry : charFreq)
				charsVector.emplace_back (entry.second, entry.first);

			// Apply Caesar shift to the customer name
			for (char & c : customerName)
			{
				if (isupper (c))
					c = 'A' + (c - 'A' + charFreq[c]) % 26;
				else c = 'a' + (c - 'a' + charFreq[c]) % 26;
			}
			// cout << "Encrypted name: " << customerName << endl << endl;

			// Apply Caesar shift to the vector of pairs
			// cout << "Characters Frequency: " << endl;
			for (const auto & entry : charsVector)
			{
				// cout << entry.second << ": " << entry.first << endl;
				// Apply Caesar shift
				char shiftedChar = entry.second;
				int shiftAmount = entry.first;

				if (isalpha (shiftedChar))
				{
					if (isupper (shiftedChar))
						shiftedChar = 'A' + (shiftedChar - 'A' + shiftAmount) % 26;
					else shiftedChar = 'a' + (shiftedChar - 'a' + shiftAmount) % 26;
				}

				// Check if the shifted character is already in the vector
				bool found = false;
				for (auto & shiftedEntry : shiftedChars)
				{
					if (shiftedEntry.second == shiftedChar)
					{
						// If found, update the frequency
						shiftedEntry.first += entry.first;
						found = true;
						break;
					}
				}
				if (!found)
					shiftedChars.emplace_back(entry.first, shiftedChar);
			}

			sort (shiftedChars.begin(), shiftedChars.end(), Compares());

			// cout << "Shifted Characters:" << endl;
			// for (const auto & entry : shiftedChars)
			// 	cout << entry.second << ": " << entry.first << endl;
			
			// Build Huffman Tree
			huffmanAVLTree.build (shiftedChars);
			// huffmanAVLTree.print();
			// cout << endl;

			if (!isalpha (huffmanAVLTree.getPair().first))
			{
				// Encode the customer name
				for (const char & c : customerName)
					resultBinaryString += huffmanAVLTree.encodedBinaryString (c);

				// Take the last 10 bits from right to left
				reverse (resultBinaryString.begin(), resultBinaryString.end());
				resultBinaryString = resultBinaryString.substr (0, min (10, (int) resultBinaryString.size()));
				result = stoi (resultBinaryString, nullptr, 2);
				huffmanAVLTree.storeDeque (HAND_customers);
			}

			huffmanAVLTree.storeDeque (HAND_customers);
			// cout << "Result binary string: " << resultBinaryString << endl;
			// cout << result << endl;

			// Assign area
			Restaurants.assignArea (result);
			// Restaurants.print();
		}

		void KOKUSEN()
		{
			if (MAXSIZE == 1) return;
			
			vector<int> bstArray;
			for (auto & entry : Restaurants.hashMap)
			{
				BinarySearchTree & bst = entry.second;
				bst.BSTpreorderTraversal (bst.getRoot(), bstArray);

				int Y = numOfWays (bstArray) % MAXSIZE;

				if (Y >= bst.size())
					bst.clear();
				else for (int i = 0; i < Y; i++)
					bst.remove (bstArray[i]);
				
				bstArray.clear();
			}
			// Restaurants.print();
		}

		void KEITEIKEN (int num)
		{
			if (num > MAXSIZE) num = MAXSIZE;
			Heap & resS = Restaurants.minheap;
			int resSize = resS.size();

			queue<HeapNode *> q = resS.getAreaToRM (num);

			while (!q.empty())
			{
				HeapNode * node = q.front();
				int index = 0;

				for (int i = 0; i < resSize; i++)
				{
					HeapNode * temp = resS.getHeap()[i];
					if (temp->label == node->label)
					{
						index = i;
						int rmSize = min (num, (int) temp->customers.size());

						for (int i = 0; i < rmSize; i++)
						{
							cout << temp->customers.front() << "-" << temp->label << endl;
							temp->customers.pop_front();
						}

						temp->order++;
						break;
					}
				}

				resS.heapifyUp (index);
				resS.removeEmpty();
				q.pop();
			}

			// Restaurants.print();
		}

		void HAND ()
		{
			if (HAND_customers.empty()) return;

			vector<string> v = HAND_customers.back();
			for (const string & s : v)
				cout << s << endl;
		}

		void LIMITLESS (int num)
		{
			map <int, BinarySearchTree> & resG = Restaurants.hashMap;

			if (resG.find (num) == resG.end()) return;

			BinarySearchTree & bst = resG[num];
			vector<string> v;
			bst.BSTinorderTraversal (bst.getRoot(), v);

			for (const string & s : v)
				cout << s << endl;
		}

		void CLEAVE (int num)
		{
			cleaveHelper (0, num);
			// Restaurants.print();
		}

	private:
		void cleaveHelper (int index, int num)
		{
			if (index >= Restaurants.minheap.size()) return;

			HeapNode * node = Restaurants.minheap.getHeap()[index];
			int remaining = min (num, (int)node->customers.size());

			// Print information for NUM customers (or all if NUM > remaining)
			for (int j = 0; j < remaining; ++j)
				cout << node->label << "-" << node->customers[node->customers.size() - 1 - j] << endl;
			
			cleaveHelper (2 * index + 1, num);
			cleaveHelper (2 * index + 2, num);
		}

		int numOfWays (vector<int> & nums) 
		{
			int n = nums.size();
			vector< vector<int> > comb(n + 1, vector<int> (n + 1));
			comb[0][0] = 1;
			for (int i = 1; i <= n; ++i) 
			{
				comb[i][0] = 1;
				for (int j = 1; j <= i; ++j)
					comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % 1000000007;
			}
			function<int(vector<int> &)> dfs = [&](vector<int> & nums) 
			{
				int n = nums.size();
				if (n <= 2) return 1;
				vector<int> left, right;
				for (int i = 1; i < n; ++i) 
				{
					if (nums[i] < nums[0]) left.push_back (nums[i]);
					else right.push_back (nums[i]);
				}
				long long res = comb[n - 1][left.size()];
				res = res * dfs(left) % 1000000007;
				res = res * dfs(right) % 1000000007;
				return (int)res;
			};
			return dfs(nums);
		}
};
// endregion

// region[rgba(255, 0, 100, 0.3)]
void simulate (string filename)
{
	Operations Operations;

	ifstream ss (filename);
	string cmd, maxsize, name, num;
	while (ss >> cmd)
	{
		if (cmd == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi (maxsize);
			// cout << "MAXSIZE: " << MAXSIZE << endl << endl;
			Operations.Restaurants = Restaurant (MAXSIZE);
		}
		else if (cmd == "LAPSE")
		{
			// cout << "=========== LAPSE ==========" << endl;
			ss >> name;
			Operations.LAPSE (name);
		}
		else if (cmd == "KOKUSEN")
		{
			// cout << "=========== KOKUSEN ==========" << endl;
			Operations.KOKUSEN ();
		}
		else if (cmd == "KEITEIKEN")
		{
			// cout << "=========== KEITEIKEN ===========" << endl;
			ss >> num;
			Operations.KEITEIKEN (stoi (num));
		}
		else if (cmd == "HAND")
		{
			// cout << "=========== HAND ===========" << endl;
			Operations.HAND ();
		}
		else if (cmd == "LIMITLESS")
		{
			// cout << "=========== LIMITLESS ===========" << endl;
			ss >> num;
			Operations.LIMITLESS (stoi (num));
		}
		else if (cmd == "CLEAVE")
		{
			// cout << "=========== CLEAVE ===========" << endl;
			ss >> num;
			Operations.CLEAVE (stoi (num));
		}
    }
}
// endregion