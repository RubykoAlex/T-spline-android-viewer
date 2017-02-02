/*
TSPLINE -- A T-spline object oriented package in C++
Copyright (C) 2015-  Wenlei Xiao

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


Report problems and direct all questions to:

Wenlei Xiao, Ph.D
School of Mechanical Engineering and Automation
Beijing University of Aeronautics and Astronautics
D-315, New Main Building, 
Beijing, P.R. China, 100191

email: xiaowenlei@buaa.edu.cn
-------------------------------------------------------------------------------
Revision_history:

2015/04/08: Wenlei Xiao
   - xxxxx.
-------------------------------------------------------------------------------
*/

/*! 
  @file demo.cpp
  @brief A demo file.

  Demos for T-spline, etc.
*/


#include "tspline.h"
#include "factory.h"
#include "editor.h"
#include "tessellator.h"
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#ifdef use_namespace
using namespace TSPLINE;
#endif

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value);
void writeObj(std::vector<TriMeshPtr> trimesh, std::string filename);
void writeObj(TriMeshPtr trimesh, std::string filename);
void writeSTLAscii(std::vector<TriMeshPtr> trimesh, std::string filename);
void writeSTLAscii(TriMeshPtr trimesh, std::string filename);
void writeSTLBinary(std::vector<TriMeshPtr> trimesh, std::string filename);
void writeSTLBinary(TriMeshPtr trimesh, std::string filename);

int main(int argc, char **argv)
{
   cout << "=====================================================\n";
   cout << " TSPLINE -- A T-spline object oriented package in C++ \n";
   cout << " DEMO program \n";
   cout << "=====================================================\n";
   cout << "usage: convert.exe [*.tsm] [option] [flag]\n";
   cout << "-[option]: obj, stla, stlb, timage, tpointset, step\n";
   cout << "-[flag]: the flag is useful only for obj, stla and stlb.\n-[1]write meshes to one file; [0](default),write meshes to multi files.\n";
   cout << "=====================================================\n";
   cout << "\n";
   
   
   std::string option;
   int flag = 0;
   if(argc<3)
   {
	   cout<<"Please read the usage."<<endl;
	   return 0;
   }
   option = argv[2];
   if(argc>3)
   {
	   flag = atoi(argv[3]);
   }
   std::transform(option.begin(),option.end(),option.begin(),::tolower);
   std::vector<std::string> optionlist;
   optionlist << "obj" << "stla" << "stlb" << "timage" << "tpointset" << "step" << "all";
   if(find(optionlist.begin(),optionlist.end(),option) == optionlist.end())
   {
	   cout<<"Please read the usage."<<endl;
	   return 0;
   }

   std::string slash;
#ifdef _WIN32
   slash = "\\";
#else
   slash = "/";
#endif
   std::string filename(argv[1]);
   int pos = filename.find_last_of(slash);
   std::string splinename(filename.substr(pos+1));
   int i = splinename.find('.');
   splinename = splinename.substr(0,i);
   std::string pathname(filename.substr(0,pos+1));
   std::string dirname = pathname + splinename;



#ifdef _WIN32
   _mkdir(dirname.c_str());
#else

#endif

   return(0);
}

std::vector<std::string>& operator<<(std::vector<std::string> &container, const std::string &value)
{
	container.push_back(value);
	return container;
}

void writeObj(std::vector<TriMeshPtr> trimesh, std::string filename)
{
}

void writeObj(TriMeshPtr trimesh, std::string filename)
{
}

void writeSTLAscii(std::vector<TriMeshPtr> trimesh, std::string filename)
{
	int i=0;
	for (std::vector<TriMeshPtr>::iterator it = trimesh.begin(); it!=trimesh.end();i++,it++)
	{
	}
}

void writeSTLAscii(TriMeshPtr trimesh, std::string filename)
{
}

void writeSTLBinary(std::vector<TriMeshPtr> trimesh, std::string filename)
{

}

void writeSTLBinary(TriMeshPtr trimesh, std::string filename)
{

}

