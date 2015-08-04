The MIT License (MIT)

Copyright (c) 2015 S74nk0 - Stanko Krstić

#pragma once

#include <algorithm>
#include <array>
#include <vector>

template <typename TYPE, typename CONTAINER> class CyclicBufferBase {
public:
	CyclicBufferBase() {}
	~CyclicBufferBase() {}

	TYPE getNext() {
		incrementIndex();
		return _buffer[_index];
	}
	void setNext(TYPE actor) {
		_buffer[_index] = actor;
		incrementIndex();
	}

	void addNext(TYPE actor) {
		_buffer.push_back(actor);
		incrementIndex();
	}

	inline CONTAINER &getContainer() { return _buffer; }

	void setIndex(const size_t index) { _index = index % _buffer.size(); }
	void shuffle() { std::random_shuffle(_buffer.begin(), _buffer.end()); }
	// fills the range
	void ranged_shuffle() {
		std::iota(_buffer.begin(), _buffer.end(), 0);
		shuffle();
	}

	// iterator wraps, comes in handy for 'for-each loops' and loops in general
	inline typename CONTAINER::iterator begin() { return _buffer.begin(); }
	inline typename CONTAINER::const_iterator begin() const { return _buffer.begin(); }
	inline typename CONTAINER::const_iterator cbegin() const { return _buffer.cbegin(); }
	inline typename CONTAINER::iterator end() { return _buffer.end(); }
	inline typename CONTAINER::const_iterator end() const { return _buffer.end(); }
	inline typename CONTAINER::const_iterator cend() const { return _buffer.cend(); }

protected:
	CONTAINER _buffer;
	size_t _index = 0;
	inline void incrementIndex() { _index = ++_index % _buffer.size(); }
};

template <typename TYPE, size_t SIZE> class CyclicBuffer : public CyclicBufferBase<TYPE, std::array<TYPE, SIZE> > {
public:
	//CyclicBuffer() { _index = SIZE - 1; } // uporabno le za DEBUGIRANJE, error na gcc
};


template <typename TYPE> class CyclicBufferDynamic : public CyclicBufferBase<TYPE, std::vector<TYPE> > {
};
