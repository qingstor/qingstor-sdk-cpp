# QingStor Service Usage Guide For C++

Import the QingStor and initialize service with a config, and you are ready to use the initialized service. Service only contains one API, and it is "ListBuckets". To use bucket related APIs, you need to initialize a bucket object.

Each API function take a Input class and return an Output class. The Input class consists of request params, request headers, request elements and request body, and the Output class holds the HTTP status code, QingStor request ID, response headers, response elements, response body and error (if error occurred).

Each API function in SDK is synchronous.

### Code Snippet

All code using the QingStor SDK and C++ should have at least the following:

```c
#include <qingstor/QingStor.h>

// Global initialization only needs to be initialized once
// Valid log levels are "none","debug", "info", "warn", "error", and "fatal".(default value is "None")
QingStor::SDKOptions sdkOptions;
sdkOptions.logLevel = Debug;
sdkOptions.logPath = "/tmp/";

QingStor::InitializeSDK(sdkOptions);

// Use the sdk
...

// Shutdown SDK wide state for the SDK. This method should be called when you are finished using the SDK.
// Do not call any other SDK methods after calling ShutdownSDK.
QingStor::ShutdownSDK(options);
```

Create the QingStor service and Bucket object with a configuration
```c
// Create QsConfig object , and init it with config info loaded form ConfigPath.
// You can also set up the config configuration item separately.
QingStor::QsConfig qsConfig;
qsConfig.LoadConfigFile("/etc/qingstor/config.yaml");

QingStorService qsService(qsConfig);
Bucket qsBucket(qsConfig, "yourbucketname", "yourzone");
```

List buckets
``` c
ListBucketsInput input;
ListBucketsOutput output;

// You can set 
input.SetLimit(200);

QsError err = qsService.ListBuckets(input, output);
// If the return value of API is "QS_ERR_NO_ERROR",
// means that you have received expected response.
if (QsError::QS_ERR_NO_ERROR == err)
{
    // You can use Output related information
    std::vector<KeyType> keys = output.GetKeys();
    printf("Got %d objects\n" ,keys.size());
}

// If the return value of API is "QS_ERR_UNEXCEPTED_RESPONSE",
// means that you have received response from QingStor, 
// but response is not expected.
// You can to know the specific cause of the mistake.
if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}

```

List objects in the bucket
```c

ListObjectsInput input;
ListObjectsOutput output;

input.SetLimit(200);

QsError err = qsBucket.ListObjects(input, output);
if (QsError::QS_ERR_NO_ERROR == err)
{
    // You can use Output related information
    std::vector<KeyType> keys = output.GetKeys();
    printf("Got %d objects\n" ,keys.size());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}

```
Put ACL of the bucket
```c
PutBucketACLInput input;
PutBucketACLOutput output;

std::vector<ACLType> aclList;
ACLType acl;
GranteeType grantee;
grantee.SetType("group");
grantee.SetName("QS_ALL_USERS");
acl.SetGrantee(grantee);
acl.SetPermission("FULL_CONTROL");
aclList.push_back(acl);
input.SetACL(aclList);

QsError err = qsBucket.PutBucketACL(input, output);
if (QsError::QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
   printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}
```

Put object with key
```c
PutObjectInput input;
PutObjectOutput output;

// object content is come from a file stream.
std::iostream * = new objectStream(new std::fstream("/tmp/Screenshot.jpg"));
objectStream->seekg(0, objectStream->end);
auto streamSize = objectStream->tellg();
objectStream->seekg(0, objectStream->beg);
input.SetBody(objectStream);
input.SetContentLength(streamSize);

QsError err = qsBucket.PutObject(objectKey, input, output);
if (QsError::QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
   printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}

// release the objectStream
if(objectStream)
    delete objectStream;
```

Delete object with key
```c
DeleteObjectInput input;
DeleteObjectOutput output;

QsError err = qsBucket.DeleteObject(objectkey, input, output);
if (QsError::QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
   printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}

```
Initialize Multipart Upload
```c
initiateMultipartUpload input;
initiateMultipartUpload output;

QsError err = qsBucket.InitiateMultipartUpload(objectkey, input, output);
if (QsError::QS_ERR_NO_ERROR == err)
{
    // Print the HTTP status code.
    printf("Got response code : %s",output.GetResponseCode());
    // Print the upload ID.
    // Example: "9d37dd6ccee643075ca4e597ad65655c"
    printf("The upload id is : %s",output.GetUploadID());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}
```
Upload Multipart
```c
// Upload the first part
UploadMultipartInput inputPart1;
UploadMultipartOutput outputPart1;

std::iostream* objectStream1 = new std::fstream(filePath1));
objectStream1->seekg(0, objectStream1->end); 
size_t streamSize1 = objectStream1->tellg(); 
objectStream1->seekg(0, objectStream1->beg); 
inputPart1.SetBody(objectStream1); 
inputPart1.SetContentLength(streamSize1);
inputPart1.SetPartNumber(1);
inputPart1.SetUploadID("9d37dd6ccee643075ca4e597ad65655c");
QsError err1 = qsBucket.UploadMultipart(objectkey, inputPart1, outputPart1);
if (QsError::QS_ERR_NO_ERROR == err1)
{
    // Print the HTTP status code.
    printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}

// release the objectStream
if(objectStream1)
    delete objectStream1;

// Upload the second part
UploadMultipartInput inputPart2;
UploadMultipartOutput outputPart2;

std::iostream* objectStream2 = new std::fstream(filePath2));
objectStream2->seekg(0, objectStream2->end); 
size_t streamSize2 = objectStream2->tellg(); 
objectStream2->seekg(0, objectStream2->beg); 
inputPart2.SetBody(objectStream2); 
inputPart2.SetContentLength(streamSize2);
inputPart2.SetPartNumber(2);
inputPart2.SetUploadID("9d37dd6ccee643075ca4e597ad65655c");

QsError err2 = qsBucket.UploadMultipart(objectkey, inputPart2, outputPart2);
if (QsError::QS_ERR_NO_ERROR == err2)
{
    // Print the HTTP status code.
    printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}
// release the objectStream
if(objectStream2)
    delete objectStream2;
```

Complete Multipart Upload
```c
std::vector<ObjectPartType> objectParts;

ObjectPartType part1,part2;
part1.SetPartNumber(1);
part2.SetPartNumber(2);
objectParts.push_back(part1);
objectParts.push_back(part2);

CompleteMultipartUploadInput input;
CompleteMultipartUploadOutput output;
input.SetUploadID("9d37dd6ccee643075ca4e597ad65655c");
input.SetObjectParts(objectParts);

QsError err = qsBucket.CompleteMultipartUpload(objectkey, input, output);
if (QsError::QS_ERR_NO_ERROR == err)
{
    // Print the HTTP status code.
    printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}
```

Abort Multipart Upload
```c
AbortMultipartUploadInput input;
AbortMultipartUploadOutput output;
input.SetUploadID("9d37dd6ccee643075ca4e597ad65655c");

QsError err = qsBucket.AbortMultipartUpload(objectkey, input, output);
if (QsError::QS_ERR_NO_ERROR == err)
{
    // Print the HTTP status code.
    printf("Got response code : %s",output.GetResponseCode());
}

if (QsError::QS_ERR_UNEXCEPTED_RESPONSE == err)
{
    ResponseErrorInfo  errorInfo = output.GetResponseErrInfo();
    printf("request_id = %s , with detail message : %s\n" , errorInfo.requestID.c_str(), errorInfo.message.c_str());
}
```