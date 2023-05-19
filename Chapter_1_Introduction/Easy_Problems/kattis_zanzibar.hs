-- Kattis - zanzibar
-- Finally some easy stuff for Haskell
-- Time: O(n), Space: O(n)
import Control.Monad
solve :: [Int] -> Int
solve arr = sum (map f (zipWith (-) (tail arr) (map (2*) arr))) where f x = max 0 x

main :: IO()
main = do
    l <- getLine
    let t = read l :: Int
    replicateM_ t (do
        l <- getLine
        let arr = init (map read (words l)) :: [Int]
        putStrLn $ show (solve arr))
