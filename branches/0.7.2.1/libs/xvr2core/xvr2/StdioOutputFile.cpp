/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include"StreamInterface.h"
#include"StdioInterface.h"
#include"StdioOutputFile.h"

namespace xvr2 {
	
	StdioOutputFile::StdioOutputFile():WriteableStream(),StdioInterface(){
	}
			
	StdioOutputFile::StdioOutputFile(const String &fname, bool for_append){
		open(fname.toCharPtr(), for_append);
	}
	
	StdioOutputFile::StdioOutputFile(FILE *__f){
		_fptr = __f;
	}
	
	StdioOutputFile::~StdioOutputFile(){
		close();
	}
	
	void StdioOutputFile::open(const String &path){
		_open(path.toCharPtr(), "w");
	}
	
	void StdioOutputFile::open(const String &path, bool for_append){
		if(for_append){
			_open(path.toCharPtr(), "a");
		}
		else{
			_open(path.toCharPtr(), "w");
		}
	}
	
	void StdioOutputFile::close(){
		_close();
	}
	
	bool StdioOutputFile::opened(){
		return _opened();
	}
	
	StdioOutputFile &StdioOutputFile::operator << (const Buffer &b){
		write((void *)b.data(), b.size());
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::operator << (const String &s){
		write((void *)s.toCharPtr(), s.size());
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::write(void *data, UInt32 __size){
		_write(data, __size);
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::write(const Buffer &b){
		write((void *)b.data(), b.size());
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::write(const String &s){
		write((void *)s.toCharPtr(), s.size());
		return *this;
	}
	
	void StdioOutputFile::seek(FileOffsetT _pos){
		//Throw an exception here
	}
	
	void StdioOutputFile::seekEnd(){
		//Throw an exception here
	}
	
	void StdioOutputFile::seekBegin(){
		//Throw an exception here
	}
	
	void StdioOutputFile::seekStep(FileOffsetT _step){
		//Throw an exception here
	}
	
	bool StdioOutputFile::eof(){
		//While writing the fd pointer is allways at EOF point
		//throw an exception here or at least return true always
		return true;
	}
};
