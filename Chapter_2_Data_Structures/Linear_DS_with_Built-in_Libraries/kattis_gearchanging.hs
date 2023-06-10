-- Kattis - gearchanging
-- The question doesn't mention the fact that gear ratio = chain teeth / back teeth and gear ratio is inversely proportional
-- to the cadence. After that, just be careful, especially in converting to double, and we are done.
import Data.List
main :: IO()
main = interact(printSol . solve . map (map read . words) . lines)

printSol :: Bool -> String
printSol True = "Ride on!"
printSol False = "Time to change gears!"

solve :: [[Int]] -> Bool
solve ([n,m,p]:xs:ys:[]) = let allGears = (sort . map (foldr1 (/)) . cp) (map (map fromIntegral) [ys, xs])
                            in all (\(x, y) -> y/x <= (fromIntegral (p+100) :: Double) / 100.0 ) (zip allGears (tail allGears))
solve _ = error "Unhandled case"

cp :: [[a]] -> [[a]]
cp [] = [[]]
cp (xs:xss) = [x:ys | x <- xs, ys <- cp xss]