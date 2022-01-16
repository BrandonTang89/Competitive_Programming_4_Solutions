{- Kattis - timeloop
I have close to no idea as to what is happening. The main algorithm part is just using a recursive funciton
as a for loop. But the IO and return value of the fun function and whatever is very unclear. I need to read more.

Time: O(n), Space: O(1)
-}
import Text.Read (readMaybe)

fun :: Integer -> Integer -> IO ()
fun 0 n = putStrLn ""
fun k n = do
    putStrLn (show (n-k+1) ++ " Abracadabra")
    fun (k-1) n

readInt :: IO (Maybe Integer)
readInt = do
    readMaybe <$> getLine

main :: IO ()
main = do
    x <- readInt
    case x of
        Nothing -> putStrLn "Invalid input"
        Just n -> fun n n