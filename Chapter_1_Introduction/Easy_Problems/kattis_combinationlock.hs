-- Kattis - combinationlock
-- Either im dumb, or the answer is incorrect because we need to move counter clockwise first then
-- clockwise then counter clockwise again. Other than that, note that our move functions should return
-- within [0, 359] and not [1, 360].
-- Also note the control structure I use to effectively do a while loop with a break :) 
-- Time: O(1), Space: O(1)

moveClockwise :: Int -> Int -> Int -- to move from a to b, takes output degrees
moveClockwise a b
    | a <= b = (b - a) * 9
    | otherwise = (40 - (a - b)) * 9

moveCounterClockwise :: Int -> Int -> Int -- to move from a to b, takes output degrees, dont move 1 extra cycle
moveCounterClockwise a b = if 360 - moveClockwise a b < 360 then 360 - moveClockwise a b else 0

solve :: IO()
solve = do
    line <- getLine
    let [ori, a, b, c] = map read (words line) :: [Int]
    if ori == 0 && a == 0 && b == 0 && c == 0
        then return ()
        else do
            print (360*2 + moveCounterClockwise ori a + 360 +  moveClockwise a b + moveCounterClockwise b c)
            solve


main :: IO()
main  = do
    solve