/*=========================================================================
  Program:   vv                     http://www.creatis.insa-lyon.fr/rio/vv

  Authors belong to:
  - University of LYON              http://www.universite-lyon.fr/
  - Léon Bérard cancer center       http://www.centreleonberard.fr
  - CREATIS CNRS laboratory         http://www.creatis.insa-lyon.fr

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the copyright notices for more information.

  It is distributed under dual licence

  - BSD        See included LICENSE.txt file
  - CeCILL-B   http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
===========================================================================*/
#ifndef clitkDD_h
#define clitkDD_h

#include <iostream>

// David's debug

#define DD(a) std::cout << #a " = [ " << a << " ]" << std::endl;std::cout.flush();
#define DDV(a,n) { std::cout << #a " = [ "; for(unsigned int _i_=0; _i_<n; _i_++) { std::cout << a[_i_] << " "; }; std::cout << " ]" << std::endl;std::cout.flush();}
  template<class T>
    void _print_container(T const& a)
    { for(typename T::const_iterator i=a.begin();i!=a.end();++i) { std::cout << *i << " "; };}
#define DDS(a) { std::cout << #a " = [ "; _print_container(a) ; std::cout << " ]" << std::endl;std::cout.flush():}

#endif
