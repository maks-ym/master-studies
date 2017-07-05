# Author: Maksym Bakhmut
#
# EDAMI lab3 2017L
# 
# The goal of the laboratory work is to find interesting sequential rules 
# in a given datasets
# 
# Steps of finding sequential rules:
# 1. Data reading and analysis
# 2. Sequential rules discovery
#
# For both of datasets will follow that path solely.
# =============================================================================
# First dataset
# =============================================================================

setwd('/home/users/mbakhmut/');
getwd()
library(arules)
library(arulesSequences)

#read data with sequences
download.file('http://staff.ii.pw.edu.pl/~gprotazi/dydaktyka/dane/diab_trans_no_header.data',
              'diab_trans_no_header.data')
?read.csv
diab.df <- read.csv("diab_trans_no_header.data", header=FALSE, stringsAsFactors = FALSE)
# we'll use codes only - remove values ($V4) because we won't use it
diab.df$V4 = NULL;
# to create baskets of transaction type save to file and read from file
write.table(diab.df, file = "MyDataDiab.csv",row.names=FALSE,col.names=FALSE, sep=",")
?read_baskets
diab.baskets = read_baskets("MyDataDiab.csv", sep =",", info = c("sequenceID","eventID")) 
# check the data
#summary
summary(diab.baskets)
str(diab.baskets)
View(as(diab.baskets, "data.frame"))

# The Code field is deciphered as follows:
# 33 = Regular insulin dose
# 34 = NPH insulin dose
# 35 = UltraLente insulin dose
# 48 = Unspecified blood glucose measurement
# 57 = Unspecified blood glucose measurement
# 58 = Pre-breakfast blood glucose measurement
# 59 = Post-breakfast blood glucose measurement
# 60 = Pre-lunch blood glucose measurement
# 61 = Post-lunch blood glucose measurement
# 62 = Pre-supper blood glucose measurement
# 63 = Post-supper blood glucose measurement
# 64 = Pre-snack blood glucose measurement
# 65 = Hypoglycemic symptoms
# 66 = Typical meal ingestion
# 67 = More-than-usual meal ingestion
# 68 = Less-than-usual meal ingestion
# 69 = Typical exercise activity
# 70 = More-than-usual exercise activity
# 71 = Less-than-usual exercise activity
# 72 = Unspecified special event

# Considering not knowing what medics need to discover/know/find in given data
# to make appropriate conclusions about connection between ways of treatment of 
# patients and the consiquences, we will try to find some dependencies.

# we can also read this data with headers (all the data is the same)
#download.file('http://staff.ii.pw.edu.pl/~gprotazi/dydaktyka/dane/diab_trans',
# 'diab_trans.data')
# we'll use the first variant of data to discover sequential rules

#setting parameters
# time(eventid) in the diab_trans.data set is given as a number of seconds from
# some date. so e.g. 600 equals to 10 minutes, 172800 - 48 hours

#for sParametr-class
# support - the minimum support of a sequence (range [0,1])
# maxsize - maximum number of items of an element of a sequence (range > 0)
# maxlen  - maximum number of elements of a sequence (range > 0)
# mingap/maxgap - the minimum/maximum  time difference between consecutive
# elements of a sequence (default none, range >= 1/range >= 0)

# we'll check different combinations of parameters

# attempt #1
# start from example parameters
# set parameter
seqParam = new("SPparameter",support = 0.5, maxsize = 2, mingap=600, maxgap=86400, 
               maxlen = 4, maxwin = (172800*6))
# apply cspade
patSeq = cspade(diab.baskets, seqParam, control = list(verbose = TRUE, 
                                                  tidLists = FALSE, summary= TRUE));
# discovery sequential rules
seqRules = ruleInduction(patSeq,confidence = 0.8)
# check the result
length(seqRules)
summary(seqRules)
inspect(sort(head(seqRules,10)))
inspect(seqRules)
# 1654 rules
# too low supports for the rules

# attempt #2
# set parameter
seqParam = new("SPparameter",support = 0.6, maxsize = 4, mingap=600, maxgap=2*172800,
               maxlen = 3, maxwin = (172800*5))

# apply cspade
patSeq = cspade(diab.baskets, seqParam, control = list(verbose = TRUE, 
                                                       tidLists = FALSE, summary= TRUE));
# discovery sequential rules
seqRules = ruleInduction(patSeq,confidence = 0.8)
# check the result
length(seqRules)
summary(seqRules)
inspect(sort(head(seqRules,50)))
inspect(seqRules)

# 163 rules
# looks better. we've got rules with much higher confidence
# On top we've got (considering confidence) some other results than just
# <{"id_62"}> => <{"id_62"}>
# Next rules show that there is no difference in their sequence
# <{"id_58"},{"id_64"}> => <{"id_64"}> 0.6060606  0.9756098 1.533101 
# <{"id_64"},{"id_58"}> => <{"id_64"}> 0.6060606  0.9756098 1.533101

# attempt #3
# set parameter
seqParam = new("SPparameter",support = 0.6, maxsize = 4, mingap=600, maxgap=172800,
               maxlen = 3, maxwin = (172800*5))

# apply cspade
patSeq = cspade(diab.baskets, seqParam, control = list(verbose = TRUE, 
                                                       tidLists = FALSE, summary= TRUE));
# discovery sequential rules
seqRules = ruleInduction(patSeq,confidence = 0.8)
# check the result
length(seqRules)
summary(seqRules)
inspect(sort(head(seqRules), by="lift", decreasing=TRUE))
inspect(sort(head(seqRules), by="confidence", decreasing=TRUE))
inspect(seqRules)

# 163 rules - means that our previous maxgap can be called as excessive 
# because number of rules didn't change
# On current step the most interesting rules are 
# <{"id_58"},{"id_64"}> => <{"id_64"}> and <{"id_64"},{"id_58"}> => <{"id_64"}>
# with onfidence = 0.9833333   and lift = 1.081667 

# attempt #4
# set parameter
??SPparameter
seqParam = new("SPparameter",support = 0.6, maxsize = 2, mingap=600, maxgap=172800, 
               maxlen = 3, maxwin = (172800*4))
# apply cspade
patSeq = cspade(diab.baskets, seqParam, control = list(verbose = TRUE, 
                                                       tidLists = FALSE, summary= TRUE));
# discovery sequential rules
seqRules = ruleInduction(patSeq,confidence = 0.8)
# check the result
length(seqRules)
summary(seqRules)
inspect(sort(head(seqRules), by="lift", decreasing=TRUE))
inspect(sort(head(seqRules), by="confidence", decreasing=TRUE))
inspect(seqRules)
# the same result because we didn't have element with more than 2 items earlier as well

# attempt #5
# we'll try to enlarge mingap trying to find seqences with consecutive elements being 
# distanciated more in time
# 100 minutes (before it was 10 minutes)
# set parameter
??SPparameter
seqParam = new("SPparameter",support = 0.6, maxsize = 2, mingap=10*600, maxgap=172800, 
               maxlen = 4, maxwin = (172800*4))
# apply cspade
patSeq = cspade(diab.baskets, seqParam, control = list(verbose = TRUE, 
                                                       tidLists = FALSE, summary= TRUE));
# discovery sequential rules
seqRules = ruleInduction(patSeq,confidence = 0.8)
# check the result
length(seqRules)
summary(seqRules)
str(seqRules)
inspect(sort(head(seqRules), by="lift", decreasing=TRUE))
inspect(sort(head(seqRules), by="confidence", decreasing=TRUE))
inspect(seqRules)
# we've got 814 sequencial rules, more than before
# let's check for example rules with more than 3 elements
subsetOfFour = subset(seqRules, (size(lhs(x))+size(rhs(x)) > 3))
length(subsetOfFour)
inspect(sort(head(subsetOfFour), by="lift"))
# first for sequential rules have the samevalues for all of three parameters
# sup = 0.6060606, conf = 0.9756098, lift = 1.533101
# <{"id_58"},{"id_58"},{"id_64"}> => <{"id_64"}>
# <{"id_62"},{"id_58"},{"id_64"}> => <{"id_64"}>
# <{"id_64"},{"id_58"},{"id_58"}> => <{"id_64"}>
# <{"id_62"},{"id_64"},{"id_58"}> => <{"id_64"}>
# considering the explanations of the codes we can deduce that after sequence of regular
# blood glucose measurements (58 - Pre-breakfast, 62 - Pre-supper and 64 - Pre-snack)
# usually the Pre-snack measurement will occure. Can deduce that we see results of 
# patients in normal/stable state


# attempt #6
# Considering the lack of knowledge in medicine we can specify a task by ourthelves.
# For example, find sequences of any events with length less than 6 that led
# to Unspecified blood glucose measurement (code 57)
# set parameter
??SPparameter
seqParam = new("SPparameter",support = 0.5, maxsize = 5, mingap=600, maxgap=172800, 
               maxlen = 6, maxwin = (172800*10))
# apply cspade
patSeq = cspade(diab.baskets, seqParam, control = list(verbose = TRUE, 
                                                       tidLists = FALSE, summary= TRUE));
# discovery sequential rules
seqRules = ruleInduction(patSeq,confidence = 0.6)
# check the result
length(seqRules)
summary(seqRules)
str(seqRules)
inspect(sort(head(seqRules), by="lift", decreasing=TRUE))
inspect(sort(head(seqRules), by="confidence", decreasing=TRUE))
inspect(seqRules)
subset_c57 = subset(seqRules, rhs(seqRules) %pin% c('id_57'))
length(subset_c57)
inspect(sort(head(subset_c57), by="lift"))
# we've got  726 sequencial rules, more than before
# Concidering rules with lift more than 1 (which means that the sequence of items in lhs
# enlarge the probability of occurance of consequent)
# we've got only rules with 1 element with one item in anticidant and one of them even the
# same (id_57). That means that occurance of one Unspecified blood glucose measurement
# or Pre-snack blood glucose measurement lead to another Unspecified blood glucose
# measurement
# <{"id_57"}> => <{"id_57"}> 0.6060606  0.9302326 1.4277988 
# <{"id_64"}> => <{"id_57"}> 0.5454545  0.8571429 1.3156146

# =============================================================================
# Second dataset
# =============================================================================
# The process of rules mining for the second dataset should be the same except
# the preprocessing of data, because we have .tar.z archive with multiple files

url = 'http://mlr.cs.umass.edu/ml/machine-learning-databases/diabetes/diabetes-data.tar.Z'
file = basename(url)
download.file(url, file)

untar(file, exdir = getwd() )
setwd('./Diabetes-Data');
getwd()
list.files()
# after extraction of files got 70 files with patients data and 3 additional files
# with help information

# read the data for the first patient
diabSeq01 <- read_baskets(con = "data-01", sep ="\t", info = c("eventDay", "eventTime",
                                                               "code", "value")) 
summary(diabSeq01)
str(diabSeq01)
View(as(diabSeq01, "data.frame"))
# after some comparison with the previous dataset we can see that it is the same
# data we have been exploring recently, so there is no use to repeat all the 
# above steps. Should admit that the second dataset is more convenient for human use.
# =============================================================================

# Conclusions:
#
# All the major notices have already been mentioned in the script above. 
# We can only generilize some points and remember some statements.
# 
# Sequential rules are useful for determining/finding different event dependencies
# with time constraints.
# Sequential rule is not a sequential pattern. Sequential rule has aditional info
# about confidence of the rule. Hence probability of event depending on other event.
# 
# In the current laboratory task got the example of using sequential rules for
# medicine. Indeed, it was too hard to get "the best sequential rules", but it was
# a good real life practice to get info from such kind of data.
# The major difficulty (problem) was the interpretation of values, because for 
# medics that numbers are eloquent and exactly tell what's happening with the 
# patient - whether he/she is in stable state or to notice some positive or negative
# dynamics. To fetch the most interesting sequential rules such information is needed.
# To get more advanced info/patterns/rules further research is needed.
