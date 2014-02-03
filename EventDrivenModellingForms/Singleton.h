#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

namespace EDM { namespace Model 
{
	template <class T>
	class Singleton
	{
		static T* _self;
		static int _refcount;
	protected:
		Singleton(){}
		virtual ~Singleton() {_self = nullptr; }
	public:
		static T* Instance();
		static bool IsExist();
		void FreeInst();
	};

	template <class T>
	T*  Singleton<T>::_self = nullptr;

	template <class T>
	int  Singleton<T>::_refcount=0;

	template <class T>
	T*  Singleton<T>::Instance()
	{
		if(!_self)
			_self = new T;
		_refcount++;
		return _self;
	}

	template <class T>
	bool Singleton<T>::IsExist()
	{
		return _self == nullptr ? false : true;
	}

	template <class T>
	void  Singleton<T>::FreeInst()
	{
		if(--_refcount == 0)
		{ 
			delete this; 
			delete _self;
			_self = nullptr; 
		}
	}
}}
#endif