#############################
#This is the gramtools library
#Helps to work with the Grammar class, like find first/follow set, parse input to create Grammar objects
#This library is not intended to be a tool-set FOR the Grammar class, 
#rather a tool to help USE the Grammar class
#############################

from grammar import Grammar

def first_set_elem(G):
    '''
    Defines the first set for every non terminal and terminal
    returns {S: [...], A : [...], B : [...]}
    
    Algorithm:
    For every terminal in the grammar G, add it to firsts, key and value as terminal itself
    Then for every non terminal in G, add its first set to the dict firsts.
    do this by calling first_r(.,.,non terminal) which adds the n_term's first set to dict
    remove duplicates in the first set of every n_term
    '''
    firsts = {}
    
    def first_r(firsts, n_term):
        '''
        when called adds the first set of the n_term to the dict firsts
        '''
        if n_term in firsts:
            return None
            #exit since n_term already exists in the dictionary

        rules = G.productions[n_term]
        firsts[n_term] = []
        for prod in rules:
            elems = prod.split(" ")
            for i in elems:
	            first_r(firsts, i)
	            firsts[n_term].extend(firsts[i])
	            if i in G.terminals or '' not in G.productions[i]:
	            	#if first non-term is nullable then we also have to include the next symbols first set
	            	#but if it is not nullable then, break
	            	break
            
    for t in G.terminals:
        firsts[t] = [t]

    for n_term in G.variables:
        if n_term not in firsts:
            first_r(firsts, n_term)

    for i in firsts:
        firsts[i] = list(set(firsts[i]))
    return firsts


def first_set_exp(G, s, firsts):
	'''
	This function takes in Grammar and a string (RHS of a production) as its paramaters
	returns a list of first set for the particular RHS
	'''
	elems = s.split(" ")
	next = True
	tup = []
	for i in elems:
		tup.extend(firsts[i])
		if i in G.terminals or '' not in G.productions[i]:
			break
	return tup


def get_grammar(string):
    '''
    function takes in lines of the grammar rules as input
    returns a Grammar instance initialized with as per given grammar rules. 
    '''
    G = Grammar()
    string = string.split('\n')
    #This loop reads every line for rules
    for line in string:
        line = line.split(" : ")
        #n_term is non terminal symbol for the rule in particular line
        n_term = line[0]
        #add the non terminal to the set of non-terminals in G
        G.add_V(n_term)
        #line contains list of possble right hand productions for the n_term
        line = line[1].split("|")
        #remove leading-trailing whitespaces
        line = map(str.strip, line)
        for p in line:
        #for each possible production of n_term
            #add the production to the grammar
            G.add_P(n_term, p)
            p = p.split(" ")
                
            for t in p:
            #for every term in the production
            #if term is not a non termianl, add it to the set of terminals for G
                if t not in G.variables:
                    G.add_T(t)
                    
            #above does not ensure that all added term is not a non terminal, 
            #so this func below will ensure correctness
        for i in G.variables:
            if i in G.terminals:
                G.terminals.remove(i)
        G.start = G.variables[0]
    return G


if __name__ == '__main__':
#    g = \
#'''S : E + E | E - E | T
#E : T * T | T / T | T
#T : int | ( S )'''
    g = \
'''E : T X
X : + E X | 
T : F Y
Y : * T Y | 
F : int | ( E )'''
    g = get_grammar(g)
    print(g)
    fr = first_set_elem(g)
    print''
    print "First set : "
    print fr
    
