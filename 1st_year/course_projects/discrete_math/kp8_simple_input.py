import matplotlib.pyplot as plt
import networkx as nx
import time
class Profiler(object):
    def __enter__(self):
        self._startTime = time.time()
         
    def __exit__(self, type, value, traceback):
        print ("Elapsed time: {:.3f} sec".format(time.time() - self._startTime))


def for_change(Relation,Basic, Words):
    word0=Relation[0]
    word1=Relation[1]
    if len(word0) > len(word1):           #расширяем словарь
        m=0;
        while m<len(Words):
            if word0==Words[m][0] and word1==Words[m][1] :
                break
            elif m==len(Words)-1:
                Words_new=[[word0,word1]]
                Words+=Words_new
                break
            else:
                m=m+1
    elif len(word0) < len(word1):
        m=0;
        while m<len(Words):
            if word1==Words[m][0] and word0==Words[m][1]:
                break
            elif m==len(Words)-1:
                Words_new=[[word1,word0]]
                Words+=Words_new
                break;
            else:
                m=m+1
                continue
    else:
        if word0>word1:
            m=0;
            while m<len(Words):
                if word0==Words[m][0] and word1==Words[m][1]:
                    break
                elif m==len(Words)-1:
                    Words_new=[[word0,word1]]
                    Words+=Words_new
                    break;
                else:
                    m=m+1
                    continue
            
        else:
            m=0;
            while m<len(Words):
                if word1==Words[m][0] and word0==Words[m][1]:
                    break
                elif m==len(Words)-1:
                    Words_new=[[word1,word0]]
                    Words+=Words_new
                    break;
                else:
                    m=m+1
                    continue
    ####
    if word0 != '':
        word0_l = word0[0]+word0
        word1_l = word0[0]+word1
        for i in range( len(Basic) ):     #упростили слова через Basic
            while word0_l.find(Basic[i][0]) != -1:
                word0_l = word0_l.replace( Basic[i][0], Basic[i][1])
            while word1_l.find(Basic[i][0]) != -1:
                word1_l = word1_l.replace( Basic[i][0], Basic[i][1])
        Relation_l = [word0_l,word1_l]
        for_change(Relation_l, Basic, Words)
        
        word0_r = word0+word0[-1]
        word1_r = word1+word0[-1]
            
        for i in range( len(Basic) ):      #упростили слова через Basic
            while word0_r.find(Basic[i][0]) != -1:
                word0_r = word0_r.replace( Basic[i][0], Basic[i][1])
            while word1_r.find(Basic[i][0]) != -1:
                word1_r = word1_r.replace( Basic[i][0], Basic[i][1])       
        Relation_r = [word0_r,word1_r]
        for_change(Relation_r, Basic, Words)
    else:
        return Words
    
    return Words
######################### конец for_change()

def is_similar(A, B):            # Есть ли общий элемент у 2х списков?
    for i in range( len(A) ):
        for j in range( len(B) ):
            if A[i]==B[j]:
                return True
            else:
                pass
    else:
        return False
    

def to_dictionary( Words ):
    i=0
    while i < len(Words):
        check=False
        j=i+1
        while j < len(Words):
            if is_similar( Words[i],Words[j] ):
                A = list( set(Words[i]+Words[j]) )
                Words[i] = []+A
                del(Words[j])
                check=True
            else:
                j+=1
        if check:
            pass
        else:
            i+=1
            
    for i in range( len(Words) ):
        pos=0 #position
        j=1
        while j < len(Words[i]) :
            if len(Words[i][pos]) > len(Words[i][j]):
                pos=j
            elif len(Words[i][pos]) == len(Words[i][j]):
                if Words[i][pos] > Words[i][j]:
                    pos=j
                else:
                    pass
            else:
                pass
            j+=1
        if pos!=0:
            Words[i][0], Words[i][pos] = Words[i][pos], Words[i][0]
        else:
            pass
    Words.sort()
    return Words


def to_node_list( Words ):
    Nlist=[]
    for i in range( len(Words) ):
       Nlist+=[ Words[i][0] ]
    return Nlist

def to_labels( Nodelist ):
    A=[]
    for i in range( len(Nodelist) ):
        tmp = Nodelist[i]
        done=''
        if tmp!='':
            degree=0
            x=0
            check=tmp[0]
            done=''
            while x < len(tmp):
                if tmp[x]==check:
                    degree+=1
                    if x!=len(tmp)-1:
                        x+=1
                        continue
         
                if degree>1:
                    done=done+check+'^'+str(degree)
                else:
                    done+=check
                if x==len(tmp)-1 and tmp[x]!=tmp[x-1]:
                    done+=tmp[x]
                degree=1
                check=tmp[x]
                x+=1

        else:
            pass
        if done=='':
            done='E'
        A+=[ (tmp,'$'+done+'$') ]
    Labels=dict(A)
    return Labels


def to_edge_list(Generator,Basic, Words):
    Elist=[]
    for i in range( len(Words) ):
        tmp = Words[i][0] + Generator
        
        for x in range( len(Basic) ):     #упростили словo через Basic
            while tmp.find(Basic[x][0]) != -1:
                tmp = tmp.replace( Basic[x][0], Basic[x][1])
                
        for j in range( len( Words ) ):
            if is_similar([tmp], Words[j]):
                Elist+=[ (Words[i][0],Words[j][0]) ]
            else:
                continue
    return Elist

def relation_to_normal( Relation,Basic ):
    word0=Relation[0]
    word1=Relation[1]
    while word1!='':
        word0+=word1[-1]
        word1+=word1[-1]
        for x in range( len(Basic) ):     #упростили словo через Basic
            while word0.find(Basic[x][0]) != -1:
                word0 = word0.replace( Basic[x][0], Basic[x][1])
            while word1.find(Basic[x][0]) != -1:
                word1 = word1.replace( Basic[x][0], Basic[x][1])
    return [word0,word1]
        

def interpretation():
    Str1=input("Введите образующие: ")
    Str=input("Введите определяющие соотношения: ")
    Str=Str.lower() 
    Str=Str.expandtabs()
    Str=Str.replace(' ','')
    Str1=Str1.lower() 
    Str1=Str1.expandtabs()
    Str1=Str1.replace(' ','')
    Generators=Str1.split(',')
    Generators = list( set(Generators).difference({''}))
    Generators.sort()
    Str=Str.split(',')
    Str = list( set(Str).difference({''}) )
    Relations_tmp = []
    Relations = []
    Basic = []

    for i in range(len(Str)):
        tmp=Str[i]
        search = tmp.rfind('^')
        while search!=-1:
            a = int(''.join(filter(lambda x: x.isdigit(), tmp[search+1:])) )
            tmp=tmp[:search-1]+tmp[search-1]*a+tmp[search+1 :].replace(str(a),'')
            search = tmp.rfind('^')
        
        tmp=tmp.split('=')
        print(tmp)
        if tmp[0] =='e':
            tmp[0]=''
        if tmp[1]=='e':
            tmp[1]=''
        tmp.sort()
        tmp.reverse()
        if set(tmp[0][0])==set(tmp[0]) and tmp[1]=='':
            Basic+=[tmp]
        else:
            Relations_tmp+=[tmp]
    if(Relations_tmp!=[]):
        for i in range(len(Relations_tmp)):
            Relations+= [relation_to_normal(Relations_tmp[i], Basic)]
    else:
        Relations=[]
    Basic.sort()
    Generators.sort()
    Relations.sort()
    return Generators, Basic, Relations

def for_one_generator(Generators,Basic):
    Words=[['']]
    for i in range(len(Generators)):
        word=Generators[i]
        for j in range(len(Basic)):
            if Basic[j][0][0]==Generators[i]:
                while word!=Basic[j][0]:
                    Words+=[[word,word]]
                    word+=Generators[i]
            else:
                pass
    Words.sort()
    return Words
    
    

################## Основная прога ########################
Generators,Basic,Relations = interpretation()
Words=[]+Basic
Colors = ['b','r','g','c','y','m','black']
Elist=[]
Nodelist=[]
Labels={}
with Profiler() as p:
    if Relations!=[]:
        for i in range( len(Relations) ):
            Words = for_change(Relations[i], Basic, Words)     
    else:
        pass
    Words += for_one_generator(Generators,Basic)
    Words = to_dictionary( Words )
    Words.sort()
for i in range( len(Generators) ):
    Elist += [to_edge_list( Generators[i],Basic, Words)]
Nodelist += to_node_list(Words)
Labels=to_labels(Nodelist)

G=nx.DiGraph()
G.add_nodes_from(Nodelist)
pos = nx.circular_layout(G)
nx.draw_networkx_nodes(G,pos, nodelist=Nodelist, node_color='w', node_size=800, alpha=0.8,linewidths=0.25,ax=None)
for i in range( len(Elist)):
    G.add_edges_from(Elist[i])
nx.draw_networkx_edges(G,pos,width=0.7,alpha=0.5,ax=None)

plt.text(-1.7, 1.25,'Generators:', style='italic',fontsize=15,bbox={'facecolor':'yellow', 'alpha':0.0,'linewidth':0.0, 'pad':4})
y=1.09
for i in range( len(Generators) ):
    nx.draw_networkx_edges(G,pos,edgelist=Elist[i],width=1.5,alpha=0.5,edge_color=Colors[ (i% len(Colors)) ], ax=None)
    plt.text(-1.3, y, Generators[i],fontsize=13,bbox={'facecolor':Colors[ (i%len(Colors)) ], 'alpha':0.5,'pad':4})
    y-=0.2

nx.draw_networkx_labels(G, pos, Labels, font_size=14.5, ax=None)
#plt.text(-1.4, 1.5, 'G= '+Str_copy, style='italic',fontsize=17,bbox={'facecolor':'white','linewidth':2, 'alpha':0.8, 'pad':3})
plt.axis('off')
plt.show()

