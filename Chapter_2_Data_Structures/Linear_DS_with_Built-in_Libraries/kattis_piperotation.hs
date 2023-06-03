-- Kattis - piperotation
-- Relatively straightforward passing through the matrix in row major order (tho column major order would work)
-- We keep track of whether we need to connect each cell to the cell above it or to the cell to the left of it
-- At the end of each row, we need to ensure we don't need to connect the last cell to the cell to the right of it
-- At the end of checking all rows, we need to ensure we don't need to connect any bottom cells to the cell below it
-- Make use of the Maybe data type to deal with the "stopping early" cases
-- Time: O(hw)
main :: IO()
main = interact (solve . tail . lines)

solve :: [String] -> String
solve xs = check (foldl attach (Just (repeat False)) xs)

attach :: Maybe [Bool] -> String -> Maybe [Bool]
attach Nothing _ = Nothing
attach (Just prev) row = attachPipe (prev, False) row []

attachPipe :: ([Bool], Bool) -> String -> [Bool] -> Maybe [Bool]
attachPipe (_, connectLeft) [] curRow = if connectLeft then Nothing else Just (reverse curRow)
attachPipe (p:ps, connectLeft) (x:xs) curRow
    | x == 'A' = if (connectLeft || p) then Nothing else attachPipe (ps, False) xs (False:curRow)
    | x == 'B' = case p of
        True -> if connectLeft then Nothing else attachPipe (ps, False) xs (True:curRow)
        False -> if connectLeft then attachPipe (ps, True) xs (False:curRow) else Nothing
    | x == 'C' = case p of
        True -> if connectLeft then attachPipe (ps, False) xs (False:curRow) else attachPipe (ps, True) xs (False:curRow)
        False -> if connectLeft then attachPipe (ps, False) xs (True:curRow) else attachPipe (ps, True) xs (True:curRow)
    | x == 'D' = case p of
        True -> if connectLeft then attachPipe (ps, True) xs (True:curRow) else Nothing
        False -> Nothing
attachPipe _ _ _ = error "Invalid input"

check :: Maybe [Bool] -> String
check Nothing = "Impossible"
check (Just xs) = if all (==False) xs then "Possible" else "Impossible"

