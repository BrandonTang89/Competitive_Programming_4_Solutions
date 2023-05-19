-- Kattis - mosquito
-- If only I had learnt abou the interact function earlier...
-- Time: O(n), Space: O(1)
solve :: String -> String
solve line = let [m, p, l, e, r, s, n] = map read (words line)
            in show (solve' m p l e r s n)
solve' :: Int -> Int -> Int -> Int -> Int -> Int -> Int -> Int
solve' m p l e r s 0 = m
solve' m p l e r s n = solve' (p `div` s) (l `div` r) (m*e) e r s (n-1)
main :: IO()
main = interact (unlines . map solve . lines)
