resource "aws_dynamodb_table" "player_score_table" {
  name           = "GameOff-2024-LeaderBoard"
  billing_mode   = "PROVISIONED"
  read_capacity  = 10
  write_capacity = 10
  hash_key       = "UserId"

  attribute {
    name = "UserId"
    type = "S"
  }

  ttl {
    attribute_name = "TimeToExist"
    enabled        = true
  }

  tags = {
   Name = "UserScoreTable"
 }
}

