# 生成根证书私钥
openssl genrsa -out ca.key 4096

# 生成根证书请求
openssl req -new -key ca.key -out ca.csr -subj "/CN=My Root CA"

# 签名根证书
openssl x509 -req -in ca.csr -signkey ca.key -out ca.crt -days 3650

# 生成中间证书私钥
openssl genrsa -out intermediate.key 4096

# 生成中间证书请求
openssl req -new -key intermediate.key -out intermediate.csr -subj "/CN=My Intermediate CA"

# 签名中间证书
openssl x509 -req -in intermediate.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out intermediate.crt -days 3650

# 生成服务器证书私钥
openssl genrsa -out server.key 2048

# 生成服务器证书请求
openssl req -new -key server.key -out server.csr -subj "/CN=mydomain.com"

# 签名服务器证书
openssl x509 -req -in server.csr -CA intermediate.crt -CAkey intermediate.key -CAcreateserial -out server.crt -days 365

# 生成客户端证书私钥
openssl genrsa -out client.key 2048

# 生成客户端证书请求
openssl req -new -key client.key -out client.csr -subj "/CN=myclient"

# 签名客户端证书
openssl x509 -req -in client.csr -CA intermediate.crt -CAkey intermediate.key -CAcreateserial -out client.crt -days 365

# 生成吊销列表的私钥
openssl genrsa -out crl.key 2048

# 生成吊销列表
openssl ca -gencrl -keyfile intermediate.key -cert intermediate.crt -out crl.pem
