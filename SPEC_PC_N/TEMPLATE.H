#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "STYPES.H"
#include "INCLUDE.H"
#include "SPECTYPES.H"

class TempString	// hmm this is a bit shitty
{
	char* pString;
	bool tDelete;
public:
	TempString(int nSize = 256) { pString = new char[nSize]; *pString = 0; tDelete = TRUE; }
	TempString(char* s) { pString = s; tDelete = FALSE; }
	~TempString() { if (tDelete) delete[] pString; }
	operator char*() { return pString; }
	TempString& operator=(TempString& r)	// assignment operator
	{
		if (this != &r)
		{
			if (!tDelete)
				pString = new char[strlen(r.pString) + 1];
			strcpy(pString, r.pString);
		}
		return *this;
	}
};


template <class TYPE> class List	// doubly linked intrusive linked list template class!!!
{
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		TYPE data;
		Node(Node* pNewPrev, Node* pNewNext)
			: pNext(pNewNext), pPrev(pNewPrev) {}
	};
	Node* m_pHead;
	Node* m_pTail;
	int m_nCount;
public:
	List()
	{
		m_pHead = 0;
		m_pTail = 0;
		m_nCount = 0;
	}
	void RemoveAll();
	~List() { RemoveAll(); }
	TYPE& NewHead();
	TYPE& NewTail();
	void AddHead(TYPE& rData)
	{
		NewHead() = rData;
	}
	void AddTail(TYPE& rData)
	{
		NewTail() = rData;
	}
	Position GetHead() { return (Position)m_pHead; }
	Position GetTail() { return (Position)m_pTail; }
	Position GetNext(Position pos)
	{
		Node* pNode = (Node*)pos;
		if (pNode)
			pNode = pNode->pNext;
		return (Position)pNode;
	}
	Position GetPrev(Position pos)
	{
		Node* pNode = (Node*)pos;
		if (pNode)
			pNode = pNode->pPrev;
		return (Position)pNode;
	}
	void Remove(Position pos);
	TYPE& operator[](Position pos) { return ((Node*)pos)->data; }
	int GetCount() { return m_nCount; }
	bool IsEmpty() { return m_nCount == 0; }
	List<TYPE>& operator=(List<TYPE>& rList);
	void Insert(TYPE& rData);
	Position Find(TYPE& rData);
};

template <class TYPE> Position List<TYPE>::Find(TYPE& rData)
{
	Node* pNode = m_pHead;
	if (!pNode)
		return nullptr;
	do
	{
		if (!(pNode->data<rData))
			return (Position)pNode;
		pNode = pNode->pNext;
	} while (pNode);
	return (Position)m_pTail;
}

template <class TYPE> void List<TYPE>::Insert(TYPE& rData)
{
	Node* pNode = m_pHead;
	if (!pNode)
	{
		AddHead(rData);
		return;
	}
	while (pNode)
	{
		if (rData<pNode->data)
		{
			Node* pPrevNode = pNode->pPrev;
			Node* pNewNode = new Node(pPrevNode, pNode);
			pNewNode->data = rData;
			if (pPrevNode == nullptr)
				m_pHead = pNewNode;
			else
				pPrevNode->pNext = pNewNode;
			pNode->pPrev = pNewNode;
			return;
		}
		pNode = pNode->pNext;
	}
	AddTail(rData);
}

template <class TYPE> void List<TYPE>::RemoveAll()
{
	Node* pNode = m_pHead;
	while (pNode)
	{
		Node* pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	m_pHead = 0;
	m_pTail = 0;
	m_nCount = 0;
}

template <class TYPE> TYPE& List<TYPE>::NewHead()
{
	Node* pNode = new Node(0, m_pHead);
	if (m_pHead)
		m_pHead->pPrev = pNode;
	else
		m_pTail = pNode;
	m_pHead = pNode;
	++m_nCount;
	return pNode->data;
}

template <class TYPE> TYPE& List<TYPE>::NewTail()
{
	Node* pNode = new Node(m_pTail, 0);
	if (m_pTail)
		m_pTail->pNext = pNode;
	else
		m_pHead = pNode;
	m_pTail = pNode;
	++m_nCount;
	return pNode->data;
}

template <class TYPE> void List<TYPE>::Remove(Position pos)
{
	Node* pNode = (Node*)pos;
	if (pNode == m_pHead)
		m_pHead = pNode->pNext;
	else
		pNode->pPrev->pNext = pNode->pNext;
	if (pNode == m_pTail)
		m_pTail = pNode->pPrev;
	else
		pNode->pNext->pPrev = pNode->pPrev;
	delete pNode;
}

template <class TYPE> List<TYPE>& List<TYPE>::operator=(List<TYPE>& rList)
{
	if (this != &rList)
	{
		RemoveAll();
		Node* pNode = rList.m_pHead;
		while (pNode)
		{
			NewTail() = pNode->data;
			pNode = pNode->pNext;
		}
	}
	return *this;
}

#define for_all(p,l) for (Position p=(l).GetHead();p;p=(l).GetNext(p))

struct GenericAdapter
{
	GUID* pGUID;						// NULL for primary device, else =&AdapterGuid
	GUID AdapterGUID;					// GUIDs of secondary devices
	TempString strDescription, strName;	// description strings
	void SetGUID(const GUID* pNewGUID)
	{
		if (pNewGUID)
		{
			AdapterGUID = *pNewGUID;
			pGUID = &AdapterGUID;
		}
		else
		{
			Zero(AdapterGUID);
			pGUID = nullptr;
		}
	}
};

class ReleaseChecker
{
	IUnknown* m_pObject;
	char* m_szName;
public:
	ReleaseChecker(IUnknown* pObject, char* szName) { m_pObject = pObject; m_szName = szName; m_pObject->AddRef(); }
	~ReleaseChecker() { int nRefCount = m_pObject->Release(); if (nRefCount) Log(LT_Error, "Oops, %s->Release() -> %d", m_szName, nRefCount); }
};


TempString ERR_Describe_RC(char* szResource);

#endif