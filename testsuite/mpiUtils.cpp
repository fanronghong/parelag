/*
  Copyright (c) 2015, Lawrence Livermore National Security, LLC. Produced at the
  Lawrence Livermore National Laboratory. LLNL-CODE-669695. All Rights reserved.
  See file COPYRIGHT for details.

  This file is part of the ParElag library. For more information and source code
  availability see http://github.com/LLNL/parelag.

  ParElag is free software; you can redistribute it and/or modify it under the
  terms of the GNU Lesser General Public License (as published by the Free
  Software Foundation) version 2.1 dated February 1999.
*/

/*
 * mpiUtils.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: villa13
 */



#include <fstream>
#include <sstream>
#include "mfem.hpp"
#include "../src/utilities/elag_utilities.hpp"

int main (int argc, char *argv[])
{

   int ierr(0);
   int num_procs, myid;

   MPI_Init(&argc, &argv);
   MPI_Comm comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &num_procs);
   MPI_Comm_rank(comm, &myid);

   RootOutput(comm, 0, std::cout, "MPIUtils test start...\n");

   int myVal = myid*myid+1;

   Array<int> globalPartialSums(num_procs+1);
   Array<int> distributedPartialSums(3);

   int total1 = ParPartialSums_Global(comm, myVal, globalPartialSums);
   int total2 = ParPartialSums_Distributed(comm, myVal, distributedPartialSums);

   if(total1 != total2)
	   ierr += 1;

   if(distributedPartialSums[0] != globalPartialSums[myid])
	   ierr += 2;

   if(distributedPartialSums[1] != globalPartialSums[myid+1])
	   ierr += 4;

   std::stringstream msg;
   msg << "globalPartialSums = ";
   globalPartialSums.Print(msg, 8);
   msg << "distributedPartialSums = ";
   distributedPartialSums.Print(msg, 3);
   if(!ierr)
	   msg << "Test passed\n";
   else
	   msg << "Test FAILED: ierr = " << ierr << "\n";

   SerializedOutput(comm, std::cout, msg.str() );

   MPI_Finalize();

   return 0;

}
