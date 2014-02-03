#pragma once

namespace EDM { namespace Model 
{
	template <class T>
	ref class RefSingleton
	{
	private:
		static T^ m_self = nullptr;

	protected:
		RefSingleton(){}

	public:
		static property T^ Instance { T^ get(); };
		static bool IsExist();
		//void FreeInst();
	};

	template <class T>
	T^  RefSingleton<T>::Instance::get()
	{
		if (m_self == nullptr)
			m_self = gcnew T;
		return m_self;
	}

	template <class T>
	bool RefSingleton<T>::IsExist()
	{
		return m_self == nullptr ? false : true;
	}

	/*template <class T>
	void  RefSingleton<T>::FreeInst()
	{
	if(--_refcount == 0)
	delete this;
	}*/
}}
