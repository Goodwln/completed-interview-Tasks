// completed-interview-Tasks
/*
    Task:
    "Implement Doubly Linked List 
     Serialization and Deserialization Functions"
*/

#include <fstream>
#include <string>
#include <random>  
#include <map>
 
class ListNode
{
public:
    ListNode* Prev;
    ListNode* Next;
    ListNode* Rand;
    std::string data;
};

class ListRand
{
public:
    ListNode* Head;
    ListNode* Tail;
    int Count;

    void Serialize(std::ofstream &s);

    void Deserialize(std::ifstream &s);
};

void ListRand::Serialize(std::ofstream& s)
{
	if (!s.is_open() || !Head)
	{
		return;
	}

	std::map<ListNode*, int> RandElement;
	RandElement[nullptr] = -1;

	ListNode* Current = Head;
	for (int i = 0; i < Count; i++)
	{
		RandElement[Current] = i;
		s << Current->data << std::endl;
		Current = Current->Next;
	}
	
	Current = Head;
	for (size_t i = 0; i < Count; i++)
	{
		const auto it = RandElement.find(Current->Rand);
		if (it->first == Current->Rand)
		{
			s << it->second << std::endl;
		}
		Current = Current->Next;
	}
}
 
		
void ListRand::Deserialize(std::ifstream &s)
{
	if (!s.is_open())
	{
		return;
	}
	
	std::map<int, ListNode*> RandElement;
	RandElement[-1] = nullptr;

	std::string str;
	std::getline(s, str);
	Head = new ListNode();
	Head->data = str;
 
	RandElement[0] = Head;
 
	if (Count > 1)
	{
		Head->Next = new ListNode();
		Head->Next->Prev = Head;

		ListNode* Current = Head->Next;
		for (int i = 1; i < Count - 1; i++)
		{
			std::getline(s, str);
			Current->data = str;
			Current->Next = new ListNode();
			Current->Next->Prev = Current;
			RandElement[i] = Current;
			Current = Current->Next;
		}

		std::getline(s, str);
		Current->data = str;
		Tail = Current;
		RandElement[Count - 1] = Tail;
	}
	

	ListNode* Current = Head;
	for (size_t i = 0; i < Count; i++)
	{
		std::getline(s, str);
		const auto it = RandElement.find(std::stoi(str));
		if (it->second)
		{
			Current->Rand = it->second;
		}
		Current = Current->Next;
	}
}
