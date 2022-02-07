/*  Ashwin Panditrao
 *  Jadhav
 *  ajadhav5
 */

#ifndef A1_HPP
#define A1_HPP

using namespace std;

int find_bucket(int num, int p){
  
  for(int x=1; x < p+1; x++){
	int bucket_range = x / p;
	if(num <= bucket_range){
	  return x - 1; 
	}
  }
  return 0;
}


void isort(std::vector<short int> Xi, MPI_Comm comm) {

    int size, rank;

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    short int buck;
    short int send;
    short int recv;
        
    sort(Xi.begin(),Xi.end());

    for(int i = 0; i< Xi.size();i++){
        buck=find_bucket(Xi[i], size-1);
        if(rank != buck){
            send = Xi[i];
            Xi.erase(Xi.begin()+i);
            MPI_Send( &send , 1 , MPI_SHORT , buck , 111 ,  comm);
            i--;
        }    
    }

    MPI_Barrier(comm);
    int sent=0;
    for(int i = 0;i<size;i++){
        if(i!=rank)MPI_Send( &sent , 1 , MPI_SHORT , i , 111 , comm);
    }
    MPI_Barrier(comm);
    
    int count=0;

    while(true){
        MPI_Recv( &recv , 1 , MPI_SHORT , MPI_ANY_SOURCE , 111 , comm , &status);
        if(recv==0){
            count++;
            if(count>=size-1)
                break;
        }
        Xi.push_back(recv-size);
    }
    MPI_Barrier(comm);
    sort(Xi.begin(),Xi.end());
    
    return; 
} // isort

#endif // A1_HPP