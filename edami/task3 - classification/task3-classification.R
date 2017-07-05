# Author: Maksym Bakhmut
#
# EDAMI lab5 - Classification
# 
# The goal of the laboratory work is to find the best classifier for a selected
# dataset
# 
# Steps of finding association rules:
#   1. Data preprocessing and analysis
#   2. Classify data using one of the methods
#   3. Adjust parameters of classifier to get the most useful classifier for 
#      our task
# 
# Data set chosen for this task is white wine
# =============================================================================

# Detailing:
# Let's consider that we want to buy the bottle of white wine. Obviously we want
# to get as good quality as possible for the limeted amount of money we have.
# Consider that we are students who care about their health, so we want to drink
# wine of quality not less than 6. And that wil be our main criterion.

# set working directory - adjust a path to your directory with datasets
setwd('/home/users/mbakhmut/');
getwd()
#library loading
library(caret)
library(party)
library(rpart)
library(e1071)

#data preparation
#Wines
#download.file('http://archive.ics.uci.edu/ml/machine-learning-databases/wine-quality/winequality-red.csv', 'wine_red.csv');
download.file('http://archive.ics.uci.edu/ml/machine-learning-databases/wine-quality/winequality-white.csv', 'wine_white.csv');
wine_ds = read.table("wine_red.csv", header = TRUE, sep=";", na.strings= "*")

str(wine_ds)
summary(wine_ds)
View(wine_ds)

# Next we'll apply our criterion to the dataset
?lapply
wine_ds$q2 = sapply(wine_ds[,12], function (x)
{
  if(x < 6) { 0 }  # "bad"
  else { 1 }       # "good"
})

# As we can observe in the dataset we have detailed information about 
# different types of wine. We can see such parameters: fixed acidity,
# volatile acidity, citric acid, residual sugar, chlorides, 
# free sulfur dioxide, total sulfur dioxide, density, pH, sulphates, alcohol
# and quality.
# The last one is the property which we consider buying wine. But
# our classifier needs all the rest parameters to give us the quality of wine.
# (classifier will estimate the quality of wine). We'll consider "good" all
# levels of quality of the wine that we would buy and "bad" all kinds of
# wine, which quality is lower than our threshold (quality = 6).
#
# It should to say, that even though, there are a lot of different measures 
# to estimate the quality of the classificator but we'll use only some of them
# because not all of the measures are good in all possible cases. In some cases
# ones will be better than others and some others can be even useless for
# current task (here we'll need only two classes in the final: "good" & "bad")

# dataset is split into two subsets: training (70%) and test (30%) in 
# a random manner

# =============================================================================
# Prepare datasets for research

#The fixed random seed makes the results repeatable
set.seed(1238)
sample_indexes <- sample(2, nrow(wine_ds), replace=TRUE, prob=c(0.7, 0.3))
sample_indexes
trainData <- wine_ds[sample_indexes==1,]
testData <- wine_ds[sample_indexes==2,]
# after splitting our dataset into training and testing datasets we'll check
# the result of sampling. We need to have examples for all qualities in both
# sets.

table(trainData$q2)
table(testData$q2)
# The result of sampling is satisfactory.

# =============================================================================
# Classification

# We will use Recursive Partitioning and Regression Tree for 
# our experiment

#myFormula  quality is a class variable, the rest are independent variables
myFormula <- (q2~ fixed.acidity + volatile.acidity + citric.acid 
              + residual.sugar + chlorides + free.sulfur.dioxide + total.sulfur.dioxide
              + density + pH + sulphates + alcohol)

#rpart
library(rpart)
?rpart

# Initial attempt to build classificator
# tree building
rpTree <- rpart(myFormula, method="class", data=trainData)

#information about a tree
printcp(rpTree)
plotcp(rpTree)

#?summary.rpart
summary(rpTree)

#graphical presentation of rpart trees
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)

#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)

#accurracy
mean(testPred == testData$q2)
#confusion matrix (contains accuracy)
confusionMatrix(testData$q2, testPred)

# Considering our parameters we need to get no results for false positive for
# class "1" (class for kinds of wine that satisfy our parameters)
# To fix that we'll try to adjust parameters.
# Attempt #1
#Matrix with errors cost
lossM=matrix(c(0,3,1,0), byrow=TRUE, nrow=2)
lossM
rpTree <- rpart(myFormula,  method="class",
                data=trainData, parms = list(loss = lossM ))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# We've got better results only having changed the cost of errors
# Attempt #2
#Matrix with errors cost
lossM = matrix(c(0,10,1,0), byrow=TRUE, nrow=2)
lossM
rpTree <- rpart(myFormula,  method="class",
                data = trainData, parms = list(loss = lossM ))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)
# Increasing error cost we got better results for training set but for test set
# results got are worse.

# We'll try to change other parameters ( rpart.control )

# Attempt #3
#changing parmaters
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 30, maxdepth = 5);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control =rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# Got better accuracy but for our goal this parameter is not as important as
# precision.

# Attempt #4
# Increasing maxDepth
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 30, maxdepth = 10);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control =rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# No effect

# Attempt #5
# Decreasing maxDepth
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 30, maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# Precision improved but overall accuracy decreased

# Attempt #6
# Here will be several trials for maxdepth below 5.
# The best result will be reported.
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 30, maxdepth = 1);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# Values 1, 3, 4 were tried but the best is maxdepth = 2

# Attempt #7
# minbucket test
# decrease
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 15, maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# minbucket = 15 -- no effect

# Attempt #8
# minbucket test
# decrease more
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 8, maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# still no effect

# Attempt #8
# minbucket test
# increase
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(minbucket = 55, maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# no effect

# Attempt #9
# minbucket test
# set to default
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# We'll use default value for minbucket

# Attempt #10
# test with different number of cross-validations
# default value = 10, so we'll decrease first
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 5, maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# no impact on results

# Attempt #11
# test with different number of cross-validations
# increase first
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 2);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# still no effect but we'll try to increase maxdepth again

# Attempt #12
# test with maxdepth again
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 10);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# result improved

# Attempt #13
# maxdepth increase
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 30);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# no effect

# Attempt #14
# maxdepth decrease (will be tested several values but chosen the best one)
lossM = matrix(c(0,3,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 6);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# for values 1 to 10 only for maxdepth = 1 or 3, we've got worse results
# but for all others it was about the same. Leave 10

# Attempt #15
# the magority of parameters for rpart.control are ised for reduction in
# calculations. In our case we haven't achieved desired result even without
# that reduction yet. We'll adjust error costs one more time.
# decrese
lossM = matrix(c(0,1,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 10);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# value = 1 is really bad
# value = 2 is much better than previous one but still not sufficient
# decreasing didn't help

# Attempt #16
# increase
lossM = matrix(c(0,15,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 6);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# such increase of error cost (up to 15) improved the result
# We'll try find the most appropriate value. After increasings and decriseangs.

# Attempt #17
# We'll try different values, brief summary above
lossM = matrix(c(0,65,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 6);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# brief description of tests
# value - observation
# 65    - almost nothing has changed, only lower accuracy, precision the same
# 10    - precision degraded
# 12    - better than 10 butdegraded in comparison to 15
# 13,14 - the same results: better than 12, worse than 15
# 16,18 - worse than 15
# 15 was a good choice

# Attempt #18
# check on other data (permutated, other seed)
set.seed(38)

sample_indexes <- sample(2, nrow(wine_ds), replace=TRUE, prob=c(0.7, 0.3))
sample_indexes
trainData <- wine_ds[sample_indexes==1,]
testData <- wine_ds[sample_indexes==2,]

lossM = matrix(c(0,15,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 5);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# Attempt #19
# check on other data (permutated, other seed)
set.seed(500)

sample_indexes <- sample(2, nrow(wine_ds), replace=TRUE, prob=c(0.7, 0.3))
sample_indexes
trainData <- wine_ds[sample_indexes==1,]
testData <- wine_ds[sample_indexes==2,]

lossM = matrix(c(0,15,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 5);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# Attempt #20
# check on other data (permutated, other seed)
set.seed(2000)

sample_indexes <- sample(2, nrow(wine_ds), replace=TRUE, prob=c(0.7, 0.3))
sample_indexes
trainData <- wine_ds[sample_indexes==1,]
testData <- wine_ds[sample_indexes==2,]

lossM = matrix(c(0,15,1,0), byrow=TRUE, nrow=2);
rpControl = rpart.control(xval = 50, maxdepth = 5);
rpTree <- rpart(myFormula,  method="class", data=trainData,
                control = rpControl,
                parms = list(split = "information", loss = lossM))
#classification of the training data
trainPred = predict(rpTree,trainData,type = "class")
table(trainData$q2,trainPred)
#classification of test data
testPred = predict(rpTree,testData,type = "class")
table(testData$q2,testPred)
#confusion matrix
confusionMatrix(testData$q2, testPred)
#accurracy
mean(testPred == testData$q2)
# plot
plot(rpTree, uniform=TRUE, main="Classification for White Wine")
text(rpTree, use.n=TRUE, all=TRUE, cex=.8)

# For three different seeds we've got the similar results (0-1 element as 
# false positive value in training set and 4-5 elements in test set).
# That means that our classificator is working stably although it's not
# perfect.

# Conclusions:
# All the major notices have already been mentioned
# in the script above. We can only generilize some issues.
# 
# For solving the classification problem we can choose from several approaches.
# We have chosen Recursive Partitioning and Regression Tree, because from among
# proposed packages there were more parameters to play with. 
# 
# After all observations it is to say that the idea that was said on the very
# beggining of the task was verified - it's impossible to create the universal
# classificator but have to adjust parameters to the current situayion/problem.
# Since our goal was formulated in such way that we needed only the minimum 
# value of precision, we haven't observed other parameters much. Only can say
# that they are not so good (for example accuracy = 0.6557).
# In addition, we didn't manage to create perfect classificator (to get FP = 0
# for all the situations). But the result is considered to be the best of 
# all attempts.
