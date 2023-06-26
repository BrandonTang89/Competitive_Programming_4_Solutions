import Data.List
main=interact(show.length.nubBy f.map(map(read::String->Int).words).tail.lines)
f [][]=True
f (x:g)(y:h)=f a c&&f b d where(a,b)=partition(<x)g;(c,d)=partition(<y)h
f _ _=False