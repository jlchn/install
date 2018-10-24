# aws cli

### installation

https://docs.aws.amazon.com/cli/latest/userguide/installing.html

### configuration

```
aws configure
```

### create security group

```
aws ec2 create-security-group --group-name "policy-test-sg" --description "policy test sg"  --vpc-id "vpc-xxx"
```

### add rule to security group

```
aws ec2 authorize-security-group-ingress --group-id sg-xxxxxx --protocol tcp --port 443 --cidr 0.0.0.0/0
```

### remove rule from security group

```
aws ec2 revoke-security-group-ingress --group-id sg-xxxxxx --protocol tcp --port 443 --cidr 0.0.0.0/0
```

### remove rule from security group

```
aws ec2 create-tags --resources sg-xxxxxx --tags Key="Name",Value="Test sg"
```


### delete security group

```
aws ec2 delete-security-group  --group-id sg-xxxxxx
```

### attach `sg-want-to-add` security group to an instance

```
aws ec2 modify-instance-attribute --instance-id i-xxxxxx --groups sg-existed-1 sg-existed-2 sg-want-to-add
```

### detach `sg-want-to-add` security group from an instance

```
aws ec2 modify-instance-attribute --instance-id i-xxxxxx --groups sg-existed-1 sg-existed-2
```
