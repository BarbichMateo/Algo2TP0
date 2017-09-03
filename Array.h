// Template de arreglo dinamico
// TODO: SEPARAR LA PARTE DE CÓDIGO EN UN .CPP

#ifndef ARRAYDIN_H
#define ARRAYDIN_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

#define DEFAULT_SIZE 10


template <class T> class Array
{
public:
	Array(size_t n); 
	Array( const Array<T> & ); 
	~Array( ); 
	size_t 		getSize( ) const; 
	Array<T>&	operator=( const Array<T> & ); 
	bool 		operator==( const Array<T> & ) const; 
	bool 		operator!=( const Array<T> & ) const; 
	T &		operator[ ]( int );
	void		append(T&);

private:
	size_t size; 
	T *ptr; 

	void 		resize(int );

};

template <class T> Array<T>::Array(size_t n=DEFAULT_SIZE)
{
	size = n;
	ptr = new T[size];
}


template <class T> Array<T>::Array( const Array<T> &init )
{
	size = init.size ;
	ptr = new T[ size ];
	for ( int i = 0; i < size; i++ )
		ptr[ i ] = init.ptr[ i ]; //debe existir el = para la clase T !
}


template <class T> Array<T>::~Array()
{
	if (ptr)
		delete [ ] ptr; 
}

template <class T> size_t Array<T>::getSize() const { return size; }

template <class T> Array<T>& Array<T>::operator=( const Array<T> &right )
{
	if ( &right != this ) {
		if ( size != right.size ){
			T *aux; 
			aux=new T[ right.size ]; 
			delete [] ptr; 
			size =right.size ; 
			ptr=aux; 
			for ( int i = 0; i < size; i++ )
				ptr[ i ] = right.ptr[ i ]; 
			return *this; 
			}
		else {
			for ( int i = 0; i < size; i++ )
				ptr[ i ] = right.ptr[ i ]; 
			return *this; 
		}
	}
	return *this;
}

template <class T> bool Array<T>::operator==( const Array<T> &right ) const
{
	if ( size != right.size )
		return false; 
	else{
		for ( int i = 0; i < size; i++ ){
			if ( ptr[ i ] != right.ptr[ i ] )
       				return false; 
		}
       	return true; 
       }
}

template <class T> bool Array<T>::operator!=( const Array<T> &right ) const
{
	if ( right == *this )
		return false;
	else
		return true;
}

template <class T> T & Array<T>::operator [ ]( int subscript )
{
	assert( (0 < subscript)|| (subscript < size) ) ; 
	return ptr[ subscript ]; 
}

template <class T> void Array<T>::resize(int new_size)
{
	T *new_ptr;

	new_ptr = new T[new_size];
	if(new_size>size){
		for(int i=0;i<size;++i){
			new_ptr[i] = (*this)[i];
		}
	}
	else{
		for(int i=0;i<new_size;++i){
			new_ptr[i] = (*this)[i];
		}
	}
	delete [] ptr;
	ptr = new_ptr;
	size = new_size;
}

template <class T> void Array<T>::append(T &new_thing)
{
	this->resize(size+1);
	(*this)[size-1] = new_thing;
}

#endif
