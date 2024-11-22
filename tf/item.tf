resource "aws_dynamodb_table_item" "item1" {
    depends_on = [
        aws_dynamodb_table.player_score_table
    ]

    table_name = aws_dynamodb_table.player_score_table.name
    hash_key = aws_dynamodb_table.player_score_table.hash_key


    item = <<ITEM
    {
        "UserId" : {"S": "001"},
        "Score" : {"N" : "100"}
    }
    ITEM
}