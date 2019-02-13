-- A binary tree
--      4
--     / \
--    2   5
--   / \
--  1   3
-- 
-- Tree table
--  node node_p
--  1    2
--  3    2
--  2    4
--  5    4
--  4    null

declare @ROOT int
declare @NODE int
declare @PARENT int

-- Output table
DECLARE @output TABLE(
    node int NOT NULL,
    role varchar(10) NOT NULL
);

set rowcount 0
select * into #mytemp from Tree

-- Find root first and delete it from #mytemp and put root into output
select @ROOT = (select node from #mytemp where node_p = null)
INSERT INTO @output (node, role) values (@ROOT, "root")
delete #mytemp where node_p = null

while @@rowcount <> 0
begin
    set rowcount 1
    select @NODE = node from #mytemp
    select @PARENT = node_p from #mytemp

    -- Check node has been appear in output first
    IF NOT EXISTS (select TOP 1 node FROM #output WHERE node = @NODE)
    BEGIN
        -- If node appears in node_p column, it's a parent node, else it's a leaf node
        IF EXISTS (select TOP 1 node_p FROM #mytemp WHERE node_p = @NODE)
        BEGIN
            insert INTO @output (node, role) values (@NODE, "middle")
        END
        ELSE
        BEGIN
            insert INTO @output (node, role) values (@NODE, "leaf")
        END
    END

    -- If parent node is not root & not appear in output table, put parent node to output table
    IF @PARENT != @ROOT
    BEGIN
        IF NOT EXISTS (select TOP 1 node FROM #output WHERE node = @PARENT)
        BEGIN 
            insert INTO @output (node, role) values (@PARENT, "middle")
        END
    END

    -- Delete node's row from #mytmp cuz we've add it into #output
    set rowcount 0
    delete #mytemp where node = @NODE
end
set rowcount 0

-- Output result
slect * from output

