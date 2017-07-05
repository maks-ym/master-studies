# author: maks-ym
# EDAMI lab7 2017L - clustering
# 
# The goal of the laboratory work is to determine the best grouping according
# to the given evaluation method.
# =============================================================================
# calculation of accuracy
accuracyCalc <- function(confTbl, startCol)
{
  corr = 0;
  for(i in startCol:ncol(confTbl))
  {
    corr = corr + max(confTbl[,i])  
  }
  accuracy = corr/sum(confTbl)
  accuracy  
}

#data set for the laboratory task
#http://archive.ics.uci.edu/ml/datasets/Cardiotocography 

download.file('http://staff.ii.pw.edu.pl/~gprotazi/dydaktyka/dane/cardioto_noClass_corr.csv','cardioto_noClass_corr.csv')
ctg_noClass <- read.csv("cardioto_noClass_corr.csv",row.names = 1)

download.file('http://staff.ii.pw.edu.pl/~gprotazi/dydaktyka/dane/cardioto_all_corr.csv','cardioto_all_corr.csv')
ctg_all <- read.csv("cardioto_all_corr.csv",row.names = 1)
# =============================================================================
# Considering the availability of the accuracy function we'll use it to
# estimate clustering quality.
# We'll use the example as a starting point for our experiments

# attempt #0
distC = dist(ctg_noClass)
card.kmeans = kmeans(distC,10)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
res3
accuracyCalc(res3,1)
# accuracy = 0.3912635 (0.4034758, 0.3926726, 0.3837482)
# (running several times got a bit different results, it's due to random seed for clustering alorithm,
# we can fix the seed and then we'll get the same results)
set.seed(986);
card.kmeans = kmeans(distC,10)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4034758 (the same after rerun the code above)
# next wil try to increase the quality of our k-means clusterization
# 10 clusters obtained

# attempt #1
# check more clusters (increase amount of clusters)
set.seed(986);
card.kmeans = kmeans(distC,12)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4147487

# attempt #2
# check more clusters (increase amount of clusters)
set.seed(986);
card.kmeans = kmeans(distC,15)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4527947
# got higher accuracy but indeed there are less clusters than 15 (there 10 
# clusters, further will use 10)

# attempt #3
# change number of the maximum number of allowed iterations (default - 10)
# will try the available minimum for iter.max, 6. Because trying 5, got the 
# warning message: 'did not converge in 5 iterations'
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 6)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# was expected to get worse result than for 10 iterations, but the accuracy
# declined not much
# acc = 0.3912635

# attempt #4
# will try the available larger values
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4034758

# attempt #5
# will try the available larger values
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 90)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# the value didn't change in comparison to 20
# acc = 0.4034758

# attempt #6
# next experiments with nstart - number of chosen random sets (default - 1)
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20, nstart = 2)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# time of calculations increased, resulting accuracy decreased
# acc = 0.3912635

# attempt #7
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20, nstart = 5)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.3912635
# nothing changed

# attempt #8
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20, nstart = 15)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.3926726
# accuracy slightly increased but still less than for nstart = 1
# we'll leave a default value (nstart = 1)

# attempt #9
# try different algorithms clustering. By default Hartigan and Wong
# algorithm is used. 
# we'll experiment with Lloyd algorithm (gere "Forgy" is the same algorithm)
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20, algorithm = "Lloyd")
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# got slightly higher accuracy
# acc = 0.4044152

# attempt #10
# in documrntation to kmeans function said that 'Hartigan and Wong' algorithm is
# the best but can occure that others are better if got appropriate value for
# nstart
# try different nstart
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20, algorithm = "Lloyd", nstart = 5)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.3767027
# got less accuracy but, in addition, got 5 warning messages "did not converge
# in 20 iterations"
# It means that the partition obtained is not stable (i.e. the algorithm did
# not converge toward an optimal solution). Indeed, a supplementary iteration 
# will modify it significantly.
# So we will try to increase iter.max parameter (the maximum number of iterations allowed)

# attempt #11
# increasing iter.max parameter
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 30, algorithm = "Lloyd", nstart = 5)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# calculation time increased considerably
# accuracy is higher than in previous experiment but still lower than for
# 'Hartigan and Wong'
# acc = 0.3912635

# attempt #12
# increasing iter.max parameter
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 50, algorithm = "Lloyd", nstart = 5)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# calculation time increases
# accuracy is higher than in previous experiment but still lower than for
# 'Hartigan and Wong'
# acc = 0.409582

# attempt #13
# increasing iter.max parameter
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 50, algorithm = "Lloyd", nstart = 10)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.409582
# accuracy didn't change. Did not manage to get such value for nstart to get 
# better results with 'Lloyd' algorithm than with 'Hartigan and Wong'

# attempt #14
# try 'MacQueen' algorithm 
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 50, algorithm = "MacQueen", nstart = 1)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.409582
# the same as previous.
# we'll change iter.max

# attempt #15
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 10, algorithm = "MacQueen", nstart = 1)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4100517
# increased a bit
# change nstart


# attempt #16
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 10, algorithm = "MacQueen", nstart = 3)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.3987788
# decreased

# attempt #17
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 10, algorithm = "MacQueen", nstart = 13)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.3973697
# increasing nstart decreasing accuracy
# will experiment with two other parameters a bit

# attempt #18
set.seed(986);
card.kmeans = kmeans(distC, centers = 10, iter.max = 20, algorithm = "MacQueen", nstart = 13)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4091123

# attempt #19
set.seed(986);
card.kmeans = kmeans(distC, centers = 12, iter.max = 20, algorithm = "MacQueen", nstart = 1)
table(card.kmeans$cluster)
res3 = table(ctg_all$CLASS,card.kmeans$cluster)
# res3
accuracyCalc(res3,1)
# acc = 0.4133396
# increased due to increament of clusters amount
# =============================================================================

# Conclusions:

# Many notices have already been mentioned in the script above. 
# 
# We carried out experiments for Cardiotocography dataset. For clustering was 
# used k-means algorithm with different paramenters. All major parameters for
# function that implements this algorithm were tested. 
# The measure of quality of our clustering was a given accuracy formula.
# Unfortunately, the best result obtained was 0.4527947 for 15 obtained 
# clusters and default other values (nstart = 1, iter.max = 10, 
# algorithm = 'Hartigan and Wong').
# The lowest one was 0.3767027 for 10 clusters, "Lloyd" algorithm, 
# 20 iterations and 5 random sets.
# After carrying out all those experiments we can conclude that k-means
# k-means algorithm is fast but the results obtained are not precise.
# This can be useful when we need fast clustering and don't need the exact
# accordance to some reference classes or we even don't have them (which 
# is more common situation).
