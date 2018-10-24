```
{
    "Version": "2012-10-17",
    "Statement": [
       {
            "Sid": "Stmt1526611323053",
            "Effect": "Allow",
            "Action": "ec2:CreateTags",
            "Resource": "arn:aws:ec2:*:*:security-group/*",
            "Condition": {
                "IpAddress": {
                    "aws:SourceIp": "0.0.0.0/0" 
                }
            }
        },
        {
            "Sid": "Stmt1526626608578",
            "Action": [
                "ec2:CreateSecurityGroup",         
                "ec2:ModifyInstanceAttribute" 
            ],
            "Effect": "Allow",
            "Resource": "*",
            "Condition": {
                "IpAddress": {
                     "aws:SourceIp": "0.0.0.0/0" 
                }
            }
        },
        {
            "Sid": "Stmt1526626600890",
            "Action": [         
                "ec2:AuthorizeSecurityGroupIngress",
                "ec2:RevokeSecurityGroupIngress", 
                "ec2:DeleteSecurityGroup",
                "ec2:UpdateSecurityGroupRuleDescriptionsIngress"        
            ],
            "Effect": "Allow",
            "Resource": "*",
            "Condition": {
              "StringEquals": {
                    "ec2:ResourceTag/Name": "test-tag-value" 
                },
                "IpAddress": {
                     "aws:SourceIp": "0.0.0.0/0"  
                }
            }
        }
    ]
}
```
