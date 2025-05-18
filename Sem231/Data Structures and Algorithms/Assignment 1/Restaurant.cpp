#include "main.h"
// extern int MAXSIZE;

class imp_res : public Restaurant
{
	class CustomerQueue;

	customer * head;
	customer * current;
	int count;

	CustomerQueue * diningList;
	CustomerQueue * waitingList;

	public:	
		imp_res () 
		{
			current = head = nullptr;
			count = 0;

			waitingList = new CustomerQueue ();
			diningList = new CustomerQueue ();
		}

		~imp_res () 
		{
			delete diningList;
			delete waitingList;
		}


// region[rgba(0, 155, 0, 0.1)]
		void firstPush (customer * cus)
		{
			this->current = cus;
			this->head = cus;
			this->head->next = this->head;
			this->head->prev = this->head;
			this->count++;

			diningList->enqueue (cus);
		}

		void clockwisePush (customer * cus)
		{
			cus->next = this->current->next;
			this->current->next->prev = cus;

			this->current->next = cus;
			cus->prev = this->current;

			this->current = cus;
			this->count++;

			diningList->enqueue (cus);
		}

		void counterClockwisePush (customer * cus)
		{
			cus->prev = this->current->prev;
			this->current->prev->next = cus;

			this->current->prev = cus;
			cus->next = this->current;

			this->current = cus;
			this->count++;

			diningList->enqueue (cus);
		}
// endregion


// region[rgba(155, 0, 0, 0.1)]
		void remove (customer * cus)
		{
			if (!cus) return;

			cus->prev->next = cus->next;
			cus->next->prev = cus->prev;

			if (cus->energy > 0)
				current = cus->next;
			else current = cus->prev;

			this->count--;
		}
// endregion

		bool duplicateName (customer * cus)
		{
			customer * tmp = this->current;

			int i = 0;
			while (i < this->count)
			{
				if (cus->name == tmp->name)
					return true;
				tmp = tmp->next;
				i++;
			}
			return false;
		}

		customer * waitListFind (int Energy)
		{
			customer * tmp = waitingList->peek();
			while (tmp && tmp->energy != Energy)
				tmp = tmp->next;
			return tmp;
		}

		void letCustomersIn()
		{
			while (!waitingList->isNull() && this->count < MAXSIZE)
			{
				customer * cus = waitingList->dequeue();
				this->RED (cus->name, cus->energy);
			}
		}


// ===================================================================================== //

// region[rgba(255, 0, 100, 0.15)]
		void RED (string name, int energy)
		{
			// cout << endl << "=== RED ===" << endl;

			customer * cus = new customer (name, energy, nullptr, nullptr);

			if (!energy || duplicateName (cus)) return;

			if (!this->count)  firstPush (cus);

			else if (this->count < MAXSIZE / 2)
			{
				if (cus->energy >= this->current->energy)
					clockwisePush (cus);
				else counterClockwisePush (cus);
			}
			else if (this->count >= MAXSIZE / 2 && this->count < MAXSIZE)
			{
				int RES = 0;
				customer * tmp = this->current;

				for (int i = 0; i < this->count; i++)
				{
					int currRes = cus->energy - tmp->energy;
					if (abs(currRes) > abs (RES))
					{
						RES = currRes;
						this->current = tmp;
					}
					tmp = tmp->next;
				}

				if (RES < 0) 
					counterClockwisePush (cus);
				else clockwisePush (cus);
			}
			else { waitingList->enqueue (cus); }
		}
// endregion


// region[rgba(50, 0, 255, 0.2)]
		void BLUE (int num)
		{
			// cout << endl << "=== BLUE ===" << endl;

			if (num > MAXSIZE) num = this->count;
			for (int i = 0; i < num; i++)
			{
				customer * tmp = diningList->dequeue();
				remove (tmp);
			}

			this->letCustomersIn();
		}
// endregion


// region[rgba(255, 0, 225, 0.2)]
		void PURPLE()
		{
			// cout << endl << "=== PURPLE ===" << endl;
			// diningList->toString("Dining");
			// LIGHT (1);
			// waitingList->toString("Waiting");
			BLUE (waitingList->purpleHelper () % MAXSIZE);
			// diningList->toString("Dining");
			// LIGHT (1);
			// waitingList->toString("Waiting");
		}
// endregion


// region[rgba(255, 255, 0, 0.15)]
		void REVERSAL()
		{
			string name = this->current->name;

			CustomerQueue tmpSorcerers;
			CustomerQueue tmpCurses;

			customer * tmp = this->current;
			for (int i = 0; i < this->count; i++)
			{
				customer * toReverse = new customer(tmp->name, tmp->energy, nullptr, nullptr);
				if (tmp->energy > 0)
					tmpSorcerers.enqueue(toReverse);
				else
					tmpCurses.enqueue(toReverse);

				tmp = tmp->prev;
			}

			tmpSorcerers.reverse();
			tmpCurses.reverse();

			for (int i = 0; i < this->count; i++)
			{
				if (tmp->energy > 0 && !tmpSorcerers.isNull())
				{
					customer *sorcerer = tmpSorcerers.dequeue();
					tmp->name = sorcerer->name;
					tmp->energy = sorcerer->energy;
				}
				else if (!tmpCurses.isNull())
				{
					customer *curse = tmpCurses.dequeue();
					tmp->name = curse->name;
					tmp->energy = curse->energy;
				}
				tmp = tmp->prev;
			}
			
			for (int i = 0; i < this->count; i++)
			{
				if (tmp->name == name)
				{
					this->current = tmp;
					break;
				}
				tmp = tmp->next;
			}
		}
// endregion


// region[rgba(0, 0, 255, 0.18)]
		void UNLIMITED_VOID ()
		{
			// cout << "=== UNLIMITED VOID ===" << endl;
			if (this->count < 4) return;

			customer * begin = nullptr;
			customer * end = nullptr;
			customer * tmp = this->current;

			int sum = 0;
			int minSum = INT32_MAX;
			int minLen = 0;

			do
			{
				for (int len = 4; len <= this->count; len++)
				{
					customer * X = tmp;
					sum = 0;
					int i = 0;
					while (i < len)
					{
						if (X == this->head) 
							X = X->next;

						sum += X->energy;
						X = X->next;
						i++;
					}

					if (sum < minSum || (sum == minSum && len >= minLen))
					{
						minSum = sum;
						minLen = len;
						begin = tmp;
						end = X;
					}
				}
				tmp = tmp->next;
			} 
			while (tmp != this->current);
			
			if (minLen < 4) return;

			tmp = begin;
			int min = INT32_MAX;
			int minIndex = 0;
			int i = 0;

			customer * minEnergy = nullptr;

			do
			{
				if (tmp->energy <= min)
				{
					min = tmp->energy;
					minIndex = i;
					minEnergy = tmp;
				}
				tmp = tmp->next;
				i++;
			} 
			while (tmp != end);
			
			tmp = minEnergy;
			for (int i = minIndex; i < minLen; i++)
			{
				tmp->print();
				tmp = tmp->next;
			}

			tmp = begin;
			for (int i = 0; i < minIndex; i++)
			{
				tmp->print();
				tmp = tmp->next;
			}
		}
// endregion


// region[rgba(0, 255, 200, 0.15)]
		void DOMAIN_EXPANSION()
		{
			// cout << endl << "=== DOMAIN EXPANSION ===" << endl;

			int sorcerersEnergy = diningList->getEnergy(true) + waitingList->getEnergy(true);
			int cursesEnergy = diningList->getEnergy(false) + waitingList->getEnergy(false);

			if (!(sorcerersEnergy && cursesEnergy)) return;

			CustomerQueue tempRemoveList;
			customer * curr = this->head;
			
			for (int i = 0; i < this->count; i++)
			{
				if (sorcerersEnergy >= abs (cursesEnergy))
				{
					if (curr->energy < 0)
						tempRemoveList.enqueue(curr);
				}
				else if (curr->energy > 0)
					tempRemoveList.enqueue(curr);

				curr = curr->next;
			}

			while (!tempRemoveList.isNull())
			{
				customer * toRemove = tempRemoveList.dequeue();
				remove (toRemove);
			}

			if (sorcerersEnergy >= abs (cursesEnergy))
			{
				waitingList->removeCurses();
				diningList->removeCurses();
			}
			else
			{
				waitingList->removeSorcerers();
				diningList->removeSorcerers();
			}

			this->letCustomersIn ();
		}

// endregion


// region[rgba(220, 220, 220, 0.2)]
		void LIGHT (int num)
		{
			if (!num)
			{
				this->waitingList->print();
				return;
			}

			customer * tmp = this->current;
			int i = 0;
			while (i < this->count)
			{
				tmp->print();
				tmp = (num < 0) ?  tmp->prev : tmp->next;
				i++;
			}
		}
// endregion

	private:
	class CustomerQueue
	{
		struct QueueNode
		{	
			customer * value;
			QueueNode * next;
			QueueNode (customer * value) 
				{ this->value = value; this->next = nullptr; }
		};

		QueueNode * front;
		QueueNode * rear;
		int size;

		public:
			CustomerQueue ()
			{
				front = rear = nullptr;
				size = 0;
			}

			~CustomerQueue ()
			{
				QueueNode * tmp = this->front;
				while (tmp)
				{
					QueueNode * toDelete = tmp;
					tmp = tmp->next;
					delete toDelete;
				}
			}

			bool isNull () { return !front; }

			customer * get (int index)
			{
				if (index < 0 || index >= this->size) return nullptr;

				QueueNode * tmp = this->front;
				int i = 0;
				while (i < index)
				{
					tmp = tmp->next;
					i++;
				}
				return tmp->value;
			}

			void set (int index, customer * val)
			{
				if (index < 0 || index >= this->size) return;

				QueueNode * tmp = this->front;
				int i = 0;
				while (i < index)
				{
					tmp = tmp->next;
					i++;
				}
				tmp->value = val;
			}

			bool contains (customer * value)
			{
				if (!value || !front) return false;

				QueueNode * tmp = this->front;
				int i = 0;
				while (i < this->size)
				{
					if (tmp->value == value)
						return true;
					tmp = tmp->next;
					i++;
				}
				return false;
			}

			int getSize () { return this->size; }

			void enqueue (customer * value)
			{
				if (this->size >= MAXSIZE) return;
				QueueNode * tmp = new QueueNode (value);

				if (!this->front)
				{
					this->front = tmp;
					this->rear  = tmp;
				}
				else
				{
					this->rear->next = tmp;
					this->rear = tmp;
				}
				this->size++;
			}

			customer * dequeue ()
			{
				if (!this->front) return nullptr;

				customer * value = this->front->value;
				this->front = this->front->next;

				if (!this->front) this->rear = this->front;

				this->size--;
				return value;
			}

			customer * peek ()
			{
				if (!this->front) return nullptr;
				return this->front->value;
			}

			void remove (customer * value)
			{
				if (!value || !front) return;

				QueueNode * prevNode = nullptr;
				QueueNode * currentNode = front;

				while (currentNode && currentNode->value != value)
				{
					prevNode = currentNode;
					currentNode = currentNode->next;
				}

				if (currentNode)
				{
					if (currentNode == front)
						front = currentNode->next;
					else prevNode->next = currentNode->next;

					if (currentNode == rear)
						rear = prevNode;

					delete currentNode;
					this->size--;
				}
			}

			void removeSorcerers()
			{
				if (this->isNull()) return;

				CustomerQueue tempQueue; // Create a temporary CustomerQueue

				QueueNode * prevNode = nullptr;
				QueueNode * currentNode = front;

				while (currentNode)
				{
					if (currentNode->value->energy > 0)
					{
						if (currentNode == front)
							front = currentNode->next;
						else
							prevNode->next = currentNode->next;

						if (currentNode == rear)
							rear = prevNode;

						QueueNode * toDelete = currentNode;
						currentNode = currentNode->next;

						// Enqueue in the temporary queue
						tempQueue.enqueue(toDelete->value);

						delete toDelete;
						this->size--;
					}
					else
					{
						prevNode = currentNode;
						currentNode = currentNode->next;
					}
				}

				tempQueue.reverse();
				while (!tempQueue.isNull())
				{
					customer *toPrint = tempQueue.dequeue();
					toPrint->print();
				}
			}

			void removeCurses()
			{
				if (this->isNull()) return;

				CustomerQueue tempQueue;

				QueueNode * prevNode = nullptr;
				QueueNode * currentNode = front;

				while (currentNode)
				{
					if (currentNode->value->energy < 0)
					{
						if (currentNode == front)
							front = currentNode->next;
						else
							prevNode->next = currentNode->next;

						if (currentNode == rear)
							rear = prevNode;

						QueueNode * toDelete = currentNode;
						currentNode = currentNode->next;

						tempQueue.enqueue(toDelete->value);

						delete toDelete;
						this->size--;
					}
					else
					{
						prevNode = currentNode;
						currentNode = currentNode->next;
					}
				}

				tempQueue.reverse();
				while (!tempQueue.isNull())
				{
					customer *toPrint = tempQueue.dequeue();
					toPrint->print();
				}
			}

			void reverse() 
			{
				QueueNode* current = front;
				QueueNode* prev = nullptr;
				QueueNode* next = nullptr;

				while (current != nullptr) 
				{
					next = current->next;
					current->next = prev;
					prev = current;
					current = next;
				}

				rear = front;
				front = prev;
			}


			int getEnergy (bool sorcerers)
			{
				if (this->isNull()) return 0;

				int energy = 0;
				QueueNode * temp = this->front;

				while (temp)
				{
					if (sorcerers && temp->value->energy > 0)
						energy += temp->value->energy;
					else if (!sorcerers && temp->value->energy < 0)
						energy += temp->value->energy;
					temp = temp->next;
				}
				return energy;
			}

			int insertionSort (int count, int incr)
			{
				int numberOfSwaps = 0;
				for (int i = incr; i < count; i += incr)
				{
					for (int j = i; (j >= incr) && abs(this->get(j)->energy) > abs(this->get(j - incr)->energy); j -= incr)
					{
						customer * tmp = this->get(j);
						this->set(j, this->get(j - incr));
						this->set(j - incr, tmp);
						numberOfSwaps++;
					}
				}
				return numberOfSwaps;
			}

			int shellSort (QueueNode * start, QueueNode* end) 
			{
				if (start == NULL || start == end) return 0;

				int count = 0;
				QueueNode * current = start;
				while (current != end->next) 
				{
					count++;
					current = current->next;
				}

				int numberOfSwaps = 0;
				for (int i = count / 2; i > 2; i /= 2)
					for (int j = 0; j < i; j++)
						numberOfSwaps += this->insertionSort(count - j, i);

				numberOfSwaps += this->insertionSort(count, 1);
				return numberOfSwaps;
			}

			int purpleHelper() 
			{
				if (this->isNull()) return 0;

				int highestEnergy = INT32_MIN;
				QueueNode * mostRecent = nullptr;
				QueueNode * temp = this->front;

				while (temp) 
				{
					if (abs(temp->value->energy) >= highestEnergy) 
					{
						highestEnergy = abs(temp->value->energy);
						mostRecent = temp;
					}
					temp = temp->next;
				}

				return this->shellSort(this->front, mostRecent);
			}

			void print ()
			{
				if (this->isNull()) return;
				QueueNode * temp = this->front;

				string output = "";
				while (temp->next != nullptr)
				{
					output += temp->value->name + "-" + to_string(temp->value->energy) + "\n";
					temp = temp->next;
				}
				output += temp->value->name + "-" + to_string(temp->value->energy);
				cout << output << endl;
			}

			void toString (const string & type = "The")
			{
				cout << type << " list: ";
				if (this->isNull())
				{
					cout << "[]" << endl;
					return;
				}

				string output = "[";
				QueueNode * temp = this->front;

				while (temp->next != nullptr)
				{
					output += temp->value->name + ": " + to_string(temp->value->energy) + ", ";
					temp = temp->next;
				}
				output += temp->value->name + ": " + to_string(temp->value->energy) + "]";

				cout << output << endl;
			}
	};
};
