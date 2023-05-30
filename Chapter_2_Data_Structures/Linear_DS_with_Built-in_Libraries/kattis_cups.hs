-- Kattis - cups
-- Nice use of a custom data type as an intance of Ord and Show
-- Time: O(n log n)
import Data.List
data Cup a = Cup String a

instance Show (Cup a) where
    show (Cup s i) = s

instance (Eq a) => Eq (Cup a) where
    (Cup s1 i1) == (Cup s2 i2) = i1 == i2

instance (Ord a) => Ord (Cup a) where
    (Cup s1 i1) <= (Cup s2 i2) = i1 <= i2

main :: IO()
main = interact(unlines . map show . sort . map (parse . words) . tail . lines)

parse :: [String] -> Cup Int
parse s = if isInt (head s) then Cup (last s) (read (head s) :: Int) else Cup (head s) (2 * read (last s) :: Int)
    where isInt :: String -> Bool
          isInt x = head x < 'a' || head x > 'z'