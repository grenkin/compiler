#ifndef SMART_PTRS_H_INCLUDED
#define SMART_PTRS_H_INCLUDED

#include <list>
#include <map>

/*
¬ программе используютс¤ "¤щики" дл¤ указателей
(термин автора программы) дл¤ безопасной обработки исключений
и дл¤ удобного освобождени¤ динамической пам¤ти.

”казатель не должен находитьс¤ в двух ¤щиках одновременно,
его можно только переложить из одного ¤щика в другой.

ќдиночный ¤щик реализуетс¤ стандартным шаблонным классом auto_ptr.
–¤д ¤щиков реализуетс¤ классом ListP.
*/

template<class T> class ListP : public std::list<T*> {

};

template<class T> class ListP<T*> : public std::list<T*> {
	void InternalCopyConstructor(ListP& d)
	{
		while (!d.empty())
			PushBack(d.PopFront());
	}
	void InternalDestructor()
	{
		for (iterator i = begin(); i != end(); ++i)
			delete (*i);
	}
public:
	ListP() {}
	ListP(ListP& d)
	{
		InternalCopyConstructor(d);
	}
    ~ListP()
	{
		InternalDestructor();
	}
	ListP& operator=(ListP& d)
	//¬ данном случае перегрузка оператора присваивани¤ об¤зательна, так как
	//при его отсутствии будет вызван оператор присваивани¤
	//базового класса std::deque<T*>, который использует конструктор копировани¤
	//этого класса. ј нужно, чтобы был вызван конструктор копировани¤ класса ListP.
	{
		if (&d != this) {
			InternalDestructor();
			InternalCopyConstructor(d);
		}
		return *this;
	}
    void PushBack(std::auto_ptr<T>& p)
    {
		push_back(p.release());
    }
    void PushFront(std::auto_ptr<T>& p)
    {
		push_front(p.release());
    }
	void Insert(iterator pos, std::auto_ptr<T>& p)
	{
		insert(pos, p.release());
	}
	std::auto_ptr<T> PopFront()
	{
		T* q = front();
		std::auto_ptr<T> p(q);
		pop_front();
		return p;
	}
	iterator Erase(iterator i)
	{
		delete (*i);
		return erase(i);
	}
	ListP CreateCopy() const
	{
		ListP d;
		for (const_iterator i = begin(); i != end(); ++i)
			d.PushBack(std::auto_ptr<T>((*i)->CreateCopy()));
		return d;
	}
};

class MapPKeyExists {};

template<class T> class MapP : public std::map<std::string, T*> {

};

template<class T> class MapP<T*> : public std::map<std::string, T*> {
public:
	MapP() {}
	MapP(MapP& m)
	{
		insert(m.begin(), m.end());
		m.clear();
	}
	~MapP()
	{
		for (iterator i = begin(); i != end(); ++i)
			delete i->second;
	}
	void Insert(const std::string& key, std::auto_ptr<T>& data)
	{
		std::pair<std::string, T*> p(key, data.release());
		std::pair<iterator, bool> r = insert(p);
		if (!r.second)
			throw MapPKeyExists();
	}
};

#endif // SMART_PTRS_H_INCLUDED
