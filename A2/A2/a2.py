'''
First Name : Ashwin Panditrao
Last Name : Jadhav
UB Name : ajadhav5
UB Number : 50405435
'''

from pyspark import RDD
from pyspark.sql import SparkSession
import time
import sys



def map_data(line):
    li = line.split(" ")
    return (int(li[1]), int(li[0]))

def reduce_data(k):
    R = k[1]
    pair = []
    for x in R:
        pair.append((x[1], x[0]))  
    return pair

if __name__ == "__main__":
    spark: SparkSession = SparkSession.builder.master("local[1]").appName("RootsCon_Components").getOrCreate()
    t1 = time.time() 
    rdd: RDD = spark.sparkContext.textFile(sys.argv[1])
    nodes: RDD = rdd.map(map_data)
    roots: RDD = nodes.filter(lambda x: x[0] == x[1])
    
    count = nodes
    while True:
        prevCount = count
        nodes1: RDD = roots.join(nodes).groupByKey().mapValues(tuple).flatMap(reduce_data)
        roots = nodes1.repartition(1)
        count = roots.count()
        if count == prevCount:
            break

    nodes1.saveAsTextFile(sys.argv[2])
    spark.stop()
    print(f"Time taken : {time.time()-t1}")