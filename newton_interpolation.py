#python 3

import math

def lin_space(x, y, jump):
	lin_list = []
	while x <= y:
		lin_list.append(x)
		x += jump
	return lin_list

def phi(xnodes, n, x):
	val = 1
	for i in range(0, n):
		val *= (x - xnodes[i])
		#print ("x: %d, xi:%d\n\t(x-xi):%d\n\tval:%d" % (x, xnodes[i],(x - xnodes[n]), val))
	return val

def pn(pn_prev, ans, xnodes, x): 
	return pn_prev + ( ans[-1] * phi(xnodes, len(ans)-1, x) )

def newton_poly(xnodes, ynodes, x):
	ans = [ynodes[0]]
	pn_prev = ynodes[0]

	for i in range(0, len(xnodes)-1):

		try: 
			#ans.append( (ynodes[i+1] - pn_prev) / (phi(xnodes, i, x)) )
			ans.append( (ynodes[i+1] - pn(pn_prev, ans, xnodes, xnodes[i])) / (phi(xnodes, i, x)) )
		except:	ans.append(0)

		pn_prev = pn(pn_prev, ans, xnodes, x)

	return pn_prev #pn(pn_prev, ans, xnodes, x)

def f(x):	
	return (3.1 * x**4) + (2.3 * x**3) - (6.6 * x**2) + (8.7*x) + 7.9


xnodes = [-1,-1,0,1,2]
ynodes = []

for node in xnodes: ynodes.append(f(node))

#xs = lin_space(-3,3, .03)
xs = lin_space(-3,3, 1)

fs = []			#actual values
ps = []			#computed values
for x in xs:
	fs.append( f(x) )
	ps.append( newton_poly(xnodes,ynodes,x) )

print (fs)
print (ps)

"""
def newton_poly(xnodes, ynodes, x):

	ans = [ynodes[0]]
	pn = lambda x: ynodes[0]

	for i in range(0, len(xnodes)-1):
		ans.append( (ynodes[i+1]) - pn(i+1) / phi (xnodes, i, i+1) )
		#pn = lambda x: pn(x) + (ans[-1] * phi(xnodes,i,x))

	return pn(x)
"""