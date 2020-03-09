#ifndef _XPLATFORM_H
#define _XPLATFORM_H

	#include <stdio.h>
#if defined(_WIN32)
	#include <memory>
	#include <stdlib.h>
	
	void _memcpy(void* _destination, const void* _source, size_t _size) {
		memcpy_s(_destination, _size, _source, _size);
	}

	void _fopen(FILE** _stream, const char* _filename, const char* _mode) {
		fopen_s(_stream, _filename, _mode);
	}

	void _fread(void* _ptr, const size_t& _bytesPerElement, const size_t& _elementSize, FILE* _stream) {
		fread_s(_ptr, _bytesPerElement * _elementSize, _bytesPerElement, _elementSize, _stream);
	}
#else
	#include <string.h>
	#include <stdint.h>
	#include <float.h>
	#include <math.h>

	static void _memcpy(void* _destination, const void* _source, size_t _size) {
		memcpy(_destination, _source, _size);
	}

	static void _fopen(FILE** _stream, const char* _fileName, const char* _mode) {
		*_stream = fopen(_fileName, _mode);
	}

	static void _fread(void* _ptr, const size_t& _bytesPerElement, const size_t& _elementSize, FILE* _stream) {
		fread(_ptr, _bytesPerElement, _elementSize, _stream);
	}
#endif

#endif