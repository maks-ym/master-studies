# Author: maks-ym
#
# EDAMI lab2
# 
# The goal of the laboratory work is to find interesting association rules 
# in a given datasets
# 
# Steps of finding association rules:
#   1. Data preprocessing and analysis
#   2. Frequent itemsets discovery
#   3. Association rules discovery
# 
# For both of datasets will follow that path solely.
#
# ==============================================================================
#
# DATASET 1: Grocery store
# ******************************************************************************
# The Groceries data set contains 1 month (30 days) of real-world point-of-sale
# transaction data from a typical local grocery outlet. The data set contains
# 9835 transactions and the items are aggregated to 169 categories.
# ******************************************************************************

# Detailing:
# Let's consider that we want to raise selling of some products that aren't
# bought very often by finding the connection between such products and 
# some products that are bought more often. The least bought products are not
# considered.

# set working directory - adjust a path to your directory with datasets
setwd('/home/users/mbakhmut/');
getwd()
# librays loading
library(arules)     # association rules
library(arulesViz)  # visualization of reles

# 1. Data preprocessing and analysis

#Groceries dataset - transactions
data(Groceries)          # load data set
?Groceries               # help
str(Groceries)           # check structure of Groceries
summary(Groceries)
inspect(head(Groceries))

# thanks to str() function we can use the appropriate slot of the data set
Groceries@transactionInfo
Groceries@data
Groceries@data@i
Groceries@data@p
Groceries@data@Dim
Groceries@data@Dimnames
Groceries@data@factors
Groceries@itemInfo        # the most useful info - hierarchy
Groceries@itemsetInfo
# As we can see the data set has already been prepared and we don't need to 
# make any cleaning (No dispensable attributes)

# build plots to see which goods and which categories of goods were bought 
# more often

# categories
pie(sort(table(Groceries@itemInfo$level2)), cex=0.55)
barplot(sort(table(Groceries@itemInfo$level2)), cex.names=0.7, las=2,
        ylab = "num of occurrences")
# supcategories (upper level)
pie(sort(table(Groceries@itemInfo$level1)))
barplot(sort(table(Groceries@itemInfo$level1)), cex.names=0.7, las=2,
        ylab = "num of occurrences")

#-----------------------------------
# Prepare items
# Because we have already had transaction type of our data set,
# we don't need convertion

# sort according  relative support values at the time of creating our table
freqTbl  = sort(itemFrequency(Groceries, type = "relative"), decreasing= TRUE)
str(freqTbl)
print(freqTbl)
summary(freqTbl)

# Consider items with supports about between '1st Qu.' and 'Median'
# and between 'Mean' and 'Max'
# We'll use this items for LHS and RHS

#printing only items having support about between '1st Qu.' and 'Median'
itemsRHS = freqTbl[freqTbl[freqTbl > 0.0038] %in% freqTbl[freqTbl < 0.010]]
length(itemsRHS)
print(itemsRHS)
barplot(itemsRHS, cex.names=0.7, las=2)
#printing only items having support about between 'Mean' and 'Max'
itemsLHS = freqTbl[freqTbl > 0.026]
length(itemsLHS)
print(itemsLHS)
str(itemsLHS)
barplot(itemsLHS, cex.names=0.7, las=2)

########################################
# 2. Frequent itemsets
# parameters of Apriori algorithm
?APparameter
aParam  = new("APparameter", "confidence" = 0.75, "support" = 0.01, "minlen"= 1,
              target ="frequent itemsets")
# print(aParam)
summary(asets)
#adjusting values of parameters
aParam@target ="frequent itemsets"

?apriori
#frequent itemsets discovery - Apriori algorithm
asets <-apriori(Groceries,aParam)
#str(asets)
#analysis of discovered frequent itemsets
length(asets)
summary(asets)
inspect(head(sort(asets, by="support"),100))

size(asets)
asets[size(asets)>2]
str(asets)

inspect(asets[size(asets)])
#charts
#plot(asets[1:10])
plot(asets[size(asets)>2], method = "graph")
inspect(asets[size(asets)>2])

#frequent itemsets discovery - Eclat algorithm
#parameters (will be used for ARs generation later)
ecParam  = new("ECparameter", "confidence" = 0.75, "support" = 0.01)
print(ecParam)

#discovery of frequent itemsets
fsets <- eclat(Groceries,ecParam)
length(fsets)
# As we can see this method gives us the same result providing the same params


#3. Association rules discovery

# setting of parameters
# starting point of adjusting and testing if parameters
aParam  = new("APparameter", "confidence" = 0.7, "support" = 0.0057, 
              "minlen"= 2,"target" = "rules")
# used minlen=2 to get rid of rules with only 1 item in it

print(aParam)                                                   # This bunch of
#Disvoering of assocation rules by means of Apriori algorithm   # code is used
aRules <-apriori(Groceries,aParam)                              # for testing
summary(aRules)                                                 # parameters.

# support > 0.0057, confidence > 0.7 => NO RULES
# support > 0.0057, confidence > 0.6 => 11 RULES
# support > 0.0057, confidence > 0.5 => 80 RULES
# support > 0.0060, confidence > 0.6 =>  8 RULES
# support > 0.0057, confidence > 0.7 => NO RULES
# we get low support because of a large dataset
# there is no sense to consider ARs with a very low confidence
# so we'll try other combinations

aParam  = new("APparameter", "confidence" = 0.7, "support" = 0.002, 
              "minlen"= 2, "maxlen" = 4, "target" = "rules")

aRules <-apriori(Groceries,aParam)                              # for testing
summary(aRules)
inspect(aRules)

# support > 0.0030, confidence > 0.80 =>  1 RULE
# support > 0.0020, confidence > 0.80 => 11 RULES
# support > 0.0030, confidence > 0.75 =>  6 RULES
# support > 0.0025, confidence > 0.75 => 14 RULES
# support > 0.0020, confidence > 0.75 => 39 RULES
# support > 0.0050, confidence > 0.70 =>  1 RULE
# support > 0.0040, confidence > 0.70 =>  5 RULES
# support > 0.0030, confidence > 0.70 => 19 RULES
# support > 0.0025, confidence > 0.70 => 36 RULES
# support > 0.0020, confidence > 0.70 => 94 RULES

length(aRules)
str(aRules)
inspect(aRules)

# discovering rules with a given consequents and antecedants (itemsRHS and itemsLHS)
# start from the last pair of parameters we've got above (support & confidence)


as(names(itemsLHS), "vector")

filteredRules = subset(aRules, subset = (rhs %in% as(names(itemsRHS), "vector")
                                         | lhs %in% as(names(itemsLHS), "vector")))
inspect(filteredRules)
# We've got the same amount of rules after filtering
# that means that every rule contains at least one item
# such as the item in itemsLHS and itemsRHS

#filtering rules - selection of interesting rules
#rules with lift parameter >2.8
filteredRulesLift <- subset(aRules, subset = lift > 2.8)
inspect(filteredRulesLift)
length(filteredRulesLift)

#charts presenting association rules
# size(filteredRulesLift)
plot(filteredRulesLift, shading="order", control=list(main = "Two-key plot" ))
plot(filteredRulesLift, method="matrix", measure="lift", interactive = TRUE)

# Now we can check and see what association rules did we get but it would be
# ineresting to check some single values of lhs items
# check what we have and choose any name
names(itemsLHS)
# for instance we'll take 'chicken'
oneRhsItemRules <- subset(filteredRulesLift, subset = lhs %in% c("chicken"))
length(oneRhsItemRules)
inspect(oneRhsItemRules)

#Selecting the rules based on the selected indicator of rules interestingness 
# Indeed we could use interestMeasure but for lift it was enough
# just to use subset function (see above)
?interestMeasure

################################################
#generation of association rules based on disvovered frequent itemsets
?ruleInduction
# ecParam declared above
#discvoring frequent itemsets
# fsets <- eclat(Groceries,ecParam)

iERules = ruleInduction(fsets, Groceries)

summary(iERules)
length(iERules)
inspect(head(iERules))

##################################################################
#datasets for the laboratory task

#Market dataset - data.frame

download.file('http://staff.ii.pw.edu.pl/~gprotazi/dydaktyka/dane/supermarket.csv','supermarket.csv')
marketSet = read.csv('supermarket.csv',sep=';')
marketSet= as.data.frame(sapply(marketSet, function(x) as.logical(x)))
head(marketSet)
# check structure
str(marketSet)
# check dimention => 4627x123
dim(marketSet)
summary(marketSet)
# we could do the pruning of names(columns)
# but we don't know exactly whether abbraviations
# are compulsory or not (they may contain necessary info)
# Indeed this data frame is a conventional matrix 2x2
# convert to transactions
marketTR = as(marketSet, "transactions")
marketTR
itemLabels(marketTR)
# as an observation should be said that 'department'
# is some kind of product but without concreate name
# check frequency of first 70 items
# (can be more, the question of readability)
itemFrequencyPlot(marketTR, topN=70,  cex.names=.6)
# we can neglect items with sup < 0.07
#(може і не треба)? departments subset
#(може і не треба)? departments <- subset(marketTR, items %pin% "department")
#(може і не треба)? department1 <-subset(marketTR, items %in% "department1")

# Discovering frequent itemsets
# Find an interesting support
# (let's about 400 observation)
nrow(marketTR)      # => 4627
400/nrow(marketTR)  # => 0.0864491
itemsets = apriori(marketTR, parameter = (list(
  target = "frequent itemsets", supp=0.086,
  minlen = 2, maxlen = 4
)))
# confidence = 0.8 (default value, is OK)
# length of itemsets is taken to get the suficient
# amount of itemsets for further research
itemsets
inspect(head(sort(itemsets), n = 10))
# add lift measure
quality(itemsets)$lift = interestMeasure(itemsets,
                                         measure="lift",
                                         trans = marketTR)
inspect(head(sort(itemsets, by = "lift"), n = 10))
plot(head(sort(itemsets, by="lift"), n = 30),
     method="graph", control=list(cex=.8) )
# Mining association rules
marketRules = apriori(marketTR, parameter = list(supp=0.086, maxlen=4))
marketRules
inspect(head(sort(marketRules, by = "lift"), n=10))
plot(marketRules)
# got the ordinary and odvious result: 
# the lower confidence or support are the more ARs we get
# but lift values differ from that observation
# can lower support for less cases
100/nrow(marketTR)  # => 0.02161228
marketRules = apriori(marketTR, parameter = list(supp=0.0216, maxlen=4))
marketRules
inspect(head(sort(marketRules, by = "lift"), n=10))
plot(marketRules)
# and we've got comparably high lift for rule
# {grocery.misc}      => {cigs.tobacco.pkts}
# check whether {grocery.misc} is a antecedant of 
# some other rules
grocerymixLHS = subset(marketRules, 
                       subset = lhs %in% "grocery.misc")
grocerymixLHS
# interesting. only 1 rule.
# that means that if someone buys {grocery.mix}
# he/she will buy {cigs.tobacco.pkts} with comparably
# high probability
# can do the opposite research with rhs itemset
# 
tissuespaperRHS = subset(marketRules, 
                       subset = rhs %in% "tissues.paper.prd")
tissuespaperRHS
# got 474 rules
inspect(head(sort(tissuespaperRHS, by = "lift"), n=300))
# laundry.needs seems to be often antecidant
# for {tissues.paper.prd} 
laundryneedsLHS = subset(tissuespaperRHS, 
                      subset = lhs %in% "laundry.needs")
laundryneedsLHS
# 129 rules => 27% of cases what is good
#
# sanitary.pads seems to be often antecidant
# for {tissues.paper.prd} as well so
sanitarypadsLHS = subset(tissuespaperRHS, 
                         subset = lhs %in% "sanitary.pads")
sanitarypadsLHS
# 114 rules => 24% of cases what is good too
# here 'good' ment the visible correlation in 
# purchasing both {sanitary.pads} with {tissues.paper}
# and {sanitary.pads} with {tissues.paper}

# Conclusions:
# All the major notices have already been mentioned
# in the script above. We can only generilize some issues.
# 
# Apriori and ECLAT algorythms are different in 
# computations and approaches but with the same 
# input parameters we got the same rules. That point
# to that the main idea of association rules is the 
# same and the output doesn't depend on the algorithm
# used for mining them.
# 
# Used measures show the probability of occurence
# of some association rules what means that such 
# rules can be used as, for example, recommendation
# for other industries but not as laws. (In our case
# such industry is Sales and might be Marketing. 
# And we can't guarantee that someone will buy 
# someyhing else because he/she buys some other 
# goods)
