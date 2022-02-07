/*  Ashwin Panditrao
 *  Jadhav
 *  ajadhav5
 */

#ifndef A1_HPP
#define A1_HPP

void keys(int rank, int Uni_Fre_Rank, int size, int Uni_Fre, std::vector<short int> &Xi, std::vector<short int> &XiAux)
{
    int keys;
    if(rank==size-1){
        keys=XiAux[Uni_Fre];
    }
    else{
        keys=XiAux[Uni_Fre_Rank]+XiAux[Uni_Fre_Rank+1];
    }

    for(int i = 0;i < keys;i++){
        if(rank==size-1){
            Xi.push_back(size-1);
        }
        else{
            if(i>=XiAux[Uni_Fre_Rank]){
                Xi.push_back(Uni_Fre_Rank-size+2);
            }
            else{
            Xi.push_back(Uni_Fre_Rank-size+1);
            }
        }
    }
}

void isort(std::vector<short int> &Xi, MPI_Comm comm)
{
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    sort(Xi.begin(),Xi.end());
        
    int Uni_Fre=2*(size-1);
    std::vector<short int> XiFre;
    std::vector<short int> XiAux(Uni_Fre+1);
    
    int count = 1;
    for (int i = 1; i < Xi.size(); i++){
        if (Xi[i] != Xi[i - 1]){
            XiFre.push_back(count);
            count = 0;
        }
        count++;
    }
    XiFre.push_back(count);   

    MPI_Reduce(&XiFre[0],&XiAux[0],Uni_Fre+1,MPI_SHORT,MPI_SUM,size-1,comm);

    MPI_Bcast(&XiAux[0],Uni_Fre+1,MPI_SHORT,size-1,comm);

    Xi.clear();
    int Uni_Fre_Rank=rank;
    keys(rank,Uni_Fre_Rank*2,size,Uni_Fre,Xi,XiAux);
    
    sort(Xi.begin(),Xi.end());
           
} // isort

#endif // A1_HPP
