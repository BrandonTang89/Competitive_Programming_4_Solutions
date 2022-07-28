-- Kattis - oddities
-- Simply use `mod`

-- Time: O(1), Space: O(1)
import Control.Monad
main :: IO()
main = do
    line <- getLine
    let n = read line :: Int
    replicateM_ n (do 
            x <- getLine
            let y = read x :: Int

            putStrLn(if (y `mod` 2) == 0 then show(y) ++ " is even" else show(y) ++ " is odd")
        )