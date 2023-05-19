-- Kattis - drinkingsong
-- Finally some easy stuff for Haskell. Similar to a problem sheet question...
-- Time: O(n), Space: O(n)
import Control.Monad
solve :: Int -> String -> String
solve 1 s = "1 bottle of " ++ s ++ " on the wall, 1 bottle of " ++ s ++ ".\nTake it down, pass it around, no more bottles of " ++ s ++ ".\n"
solve 2 s = "2 bottles of " ++ s ++ " on the wall, 2 bottles of " ++ s ++ ".\nTake one down, pass it around, 1 bottle of " ++ s ++ " on the wall.\n\n" ++ solve 1 s
solve n s = (show n ++ " bottles of " ++ s ++ " on the wall, " ++ show n ++ " bottles of " ++ s ++ ".\nTake one down, pass it around, " ++ show (n-1) ++ " bottles of " ++ s ++ " on the wall.\n\n") ++ solve (n-1) s

main :: IO()
main = do
    l <- getLine
    let n = read l :: Int
    s <- getLine

    putStrLn (solve n s)
