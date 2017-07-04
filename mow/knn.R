##
 # Copyright (C) 2017-01-24 Maks-ym (hereafter "Author")
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documentation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 # of the Software, and to permit persons to whom the Software is furnished to do
 # so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in all
 # copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 # INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 # PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
 # DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 # FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 #
 # Except as contained in this notice, the name of the Author shall not be used in advertising or
 # otherwise to promote the sale, use or other dealings in this Software without prior written
 # authorization from the Author.
 # 
 # R Project - k-NN algorithm
 ##

setwd("/MOW/Project/") #full path to project

# packages to use
# install.packages("stringr", dependencies = TRUE)
library(stringr)

#[STEP 1] -- load data into appropriate structure

#[DOC] function to clean the line (punctuation, tolower, webaddresses, phonenumbers)
clean_line <- function(line) {
	line = tolower(line);
	line = str_replace_all(line,"[http://]*www[a-zA-Z0-9\\.]+", " wbst ")	#websites
	line = str_replace_all(line,"[0-9]{11}", " phnnmbr ")				#11 numbers to phonenumber
	line = str_replace_all(line,"[^a-zA-Z]", " ")					#only letters left
	line = str_replace_all(line,"xxx\\s*$", "msgend")				#xxx(from the end)->msgend
	line = str_replace_all(line,"xxx", " xxx ")					#отделяем xxx (porn)
	line = str_replace_all(line,"\\s+", " ")						#single spaces
	return(line);
}

#[DOC] remove_stop_words - line must be prepared vector of strings ([[1]])
remove_stop_words <- function(words) {
	stopwords = c("a","about","above","after","again","against","all","am","an","and","any","are","aren't",
		"as","at","be","because","been","before","being","below","between","both","but","by","cant","cannot",
		"could","couldnt","did","didnt","do","does","doesnt","doing","dont",
		"down","during","each","few","for","from","further","had",
		"hadnt","has","hasnt","have","havent","having","he","hed",
		"hell","hes","her","here","here's","hers","herself","him","himself","his",
		"how","how's","i","id","ill","im","ive","if","in","into","is","isnt",
		"it","its","itself","lets","me","more","most","mustnt","my",
		"myself","no","nor","not","of","off","on","once","only","or","other","ought","our","ours",
		"ourselves","out","over","own","same","shant","she","shed","shell","shes","should","shouldnt","so",
		"some","such","than","that","thats","the","their","theirs","them","themselves","then","there",
		"theres","these","they","theyd","theyll","theyre","theyve","this","those","through","to","too","under",
		"until","up","very","was","wasn't","we","wed","well","were","weve","were","werent","what","whats",
		"when","whens","where","wheres","which","while","who","whos","whom","why","whys","with","wont",
		"would","wouldnt","you","youd","youll","youre","youve","your","yours","yourself","yourselves"
	);
	words= words[!words %in% stopwords];
	return(words);
}


#[DOC] function to create DF of messages - returns data frame with 2 columns ('class', 'msg')
read_lines_classified <- function(file.name) {
	handle <- file(file.name, "rt");					#open file
	lines  <- readLines(handle);						#read file
	close(handle);								#close file
	
	#create empty data frame
	new_df = data.frame(class=character(), msg=character(), stringsAsFactors = FALSE);
	df_length = length(new_df[1]);
	for(l in lines) {
		l = str_split(l, "\t")[[1]];
		l[2] = clean_line(l[2]);
		l[2] = remove_stop_words(l[2][[1]]);
		#new_df = rbind(new_df, l);
		#df_length = ifelse((df_length==1), 1, length(new_df[1])+1 );
		new_df[df_length, ] = c(l[1], l[2]);
		df_length = df_length + 1;
	}

	return(new_df);
}

#######training

# [INTRO] we have 5574 records (SMS messages)
# we devide them into 2 sets: training and test sets

# [STEP] -- Create the model - matrix or array (something dynamic)
# add each example one by one checking 
# searching each word in the already created table
## if there is such word -> put the "weigt" in the appropriate cell
## if not -> create new row (word)

# [STEP] -- After data set divided into 2 subsets: training & testing 
# Create model (table of weights) | Choose formula for weights calculation

create_word_matrix <- function(train_set) {

# get data frame: class | message
# RETURN df of words.
# rows represent messages, cols - words.
# if word is in the message - 1, otherwise - 0

	words = c();
	for(i in 1:nrow(train_set)) {
		tmp = unlist(str_split(train_set[i,2], " "));
		words = c(words, tmp);
	}
	words = table(words);				# count number of repetitions of each word
	words = words[words>30];			# remove all words whitch met less then 6 times in all set
	words = words[words<350];
	words = words[nchar(names(words))>2];	#remove all words shorter then 3 letters
	words = remove_stop_words(names(words));
	model = data.frame(class=train_set[1], stringsAsFactors = FALSE);
	model[words] = 0;					# add columns
	for(i in 1:nrow(model)) {
		current_row = unlist(str_split(train_set[i,2], " "));
		current_row = table(current_row);
		current_row = remove_stop_words(names(current_row));
		model[i, words %in% current_row] = 1;
	}
	model["class"] = NULL;				#remove info about classes
	return(model);					#return only word_matrix
}

# [STEP] -- kNN Prediction (k = 5)
# Use temp table of size k ( = 5)
# Use cosine similarity

metric_cos <- function(v1,v2,v1n,v2n) {
#v1,	v2	- (vector) 0|1 values
#v1n, v2n	- (number) norm of vector -> sqrt(sum(v^2))
  return ((sum (v1*v2)) / (v1n * v2n));
}

metric_euc <- function(v1,v2) {
  return (sqrt (sum ((v2 - v1)^2)))
}

knn <- function(model, test, classes, k, metric, model_norm, test_norm) {

# model, test		- (df)		word matrices (just selected indices)
# classes			- (vector)		classes of model samples
# k				- (number)		num of neighbours
# metric			- (character)	'c' for cosine OR 'e' for euclidic
# model_norm, test_norm	- (vector)		norms of vectors (to push into cosine metric)

	row_num_model = nrow(model);
	row_num_test  = nrow(test);
	result = c();			# (vector) - predicted classes for test set
	distances = c();
	for (i in 1:row_num_test){
		# count all distanses
		if(metric == 'c') {
			for(j in 1:row_num_model) {
				distances[j] = metric_cos(model[j,], test[i,], model_norm[j], test_norm[i]);
			}
		}
		else {
			for(j in 1:row_num_model) {
				distances[j] = metric_euc(model[j,], test[i,]);
			}
		}
		# voting
		distances = order(distances,decreasing=FALSE); #это индексы
		#distances = distances[1:k];
		voters = classes[distances];
		current_prediction = voters[max(table(voters))];
		result = c(result, current_prediction);
	}
	return(result);
}

count_norms <- function(d) {
#d	- (dataframe) processed dataframe where cols - words, cells - 0|1
# RETURN norms for each row. it's used for cosine metric
	rows = nrow(d);
	norms = numeric(rows);
	for(i in 1:rows) {
		norms[i] = sqrt(sum(d[i,]^2));
	}
	return(norms);
}


correct_rate <- function(v1,v2) {
# - check the ratio of correct predictions to all true classes
# v1 - true classes
# v2 - predicted classes
# RETURN vector of prediction correctness (overall, ham, spam)
	
	if(length(v1)!=length(v2)) {
		stop(paste("Error. Vectors must be of the same length."));
	}
	else {
		correct_ham = 0;
		correct_spam = 0;
		for(i in 1:length(v1)) {
			if(v1[i] == v2[i]) {
				if(v1[i]=="ham") {
					correct_ham = correct_ham + 1;
				}
				else {
					correct_spam = correct_spam + 1;
				}
			}
		}
		ham_proportion = 	correct_ham/table(v1)["ham"];
		spam_proportion = correct_spam/table(v1)["spam"];
		overall_correctness = (correct_ham+correct_spam)/(length(v1));
		
		return(c(overall_correctness, ham_proportion, spam_proportion));
	}
}

# [TESTING PROGRAM]

d = read_lines_classified("SMSSpamCollection");
set_matrix = create_word_matrix(d);	#convert all the data to dataframe (rows - message indices, cols - words)
set_norms = count_norms(set_matrix);

model = set_matrix[4250:4600,];
test = set_matrix[1265:1285,];
model_norms = set_norms[4250:4600];
test_norms = set_norms[1265:1285];
model_classes = d[4250:4600,1];
test_classes = d[1265:1285,1];	#true classes to compare with

results = data.frame(metric=character(6), k=numeric(6), overall=numeric(6), stringsAsFactors = FALSE);
results[c("ham", "spam")] = 0;
for(i in seq(2, 10, by=2)) {
	prediction_vector = knn(model, test, model_classes, i, 'e', model_norms, test_norms);
	correct_rate(test_classes, prediction_vector);
	results[i-1,] = c('e', i, correct_rate(test_classes, prediction_vector));
	prediction_vector = knn(model, test, model_classes, i, 'c', model_norms, test_norms);
	correct_rate(test_classes, prediction_vector);
	results[i,] = c('c', i, correct_rate(test_classes, prediction_vector));
}

##train 	test
# 1:250	5561:5574
# 420:740	51:75
# 4250:4600	1265:1285
