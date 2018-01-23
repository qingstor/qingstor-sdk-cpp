# QingStor Service Usage Guide For C

Import the QingStor and initialize service with a config, and you are ready to use the initialized service. 

Each API function take a Input struct and return an Output struct. The Input struct consists of request params, request headers, request elements and request body, and the Output holds the HTTP status code, QingStor request ID, response headers, response elements, response body and error ( if error occurred ).

Every member variable in Input struct is defined for type "Pointer", The user needs to ensure that corresponding memory space for these member variables is vaild when API synchronously blocking. Each API function in SDK is synchronous. All Input struct and custom struct( e.g. "qs_grantee_t" ) should be initialized by corresponding initialization function( e.g. "init_put_bucket_acl_input" adn "init_grantee" ).

### Code Snippet

All code using the QingStor SDK and C should have at least the following:

```c
#include "qingstor/service_with_c_style/QingStorCStyle.h"

// Global initialization only needs to be initialized once
// Valid log levels are "Verbose","Debug", "Info", "Warning", "Error", "Fatal" and "None".(default value is "None")
qs_init_sdk("/tmp/", LogLevel::Debug, 1);

// Create qs_context_handle, which is used in every API. 
qs_context_handle context_hdl = qs_create_service_with_configfile(strConfigPath, strBucketName, strZone);

// Use the sdk
...

// Release context_hdl 
qs_release_service(qs_context_handle context_hdl);

// Shutdown SDK wide state for the SDK. This method should be called when you are finished using the SDK.
// Do not call any other SDK methods after calling ShutdownSDK.
qs_shutdown_sdk(1);
```

List buckets
``` c
qs_list_buckets_output_t output;
qs_list_buckets_input_t input;

//Initialize the input variable before calling the function
init_list_buckets_input(&input);

QsError err = qs_list_buckets(&input,&output,context_hdl);
if ( QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
    printf("%d\n",output->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}

//Release output the when it is no longer needed.
release_list_buckets_output(&output);
```

List objects in the bucket
```c
qs_list_objects_output_t output;
qs_list_objects_input_t input;

// Initialize the input variable before calling the function
init_list_objects_input(&input);

// Setting input parameters
int limit = 200;
input->limit =&limit;

QsError err = qs_list_objects(&input,&output,context_hdl);
if ( QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
    // Example: 200
    printf("%d\n",output->response_code);

    // Print the key count.
    // Example: 0
    printf("%d\n",output.GetKeys());
}

//Release output the when it is no longer needed.
release_list_buckets_output(&output);
```

Put ACL of the bucket
```c
qs_put_bucket_acl_input_t input;
qs_put_bucket_acl_output_t output;

//Initialize the input variable before calling the function.
init_put_bucket_acl_input (&input);

// define and init acl variable.
qs_acl_t acl;
init_acl (&acl);

// define and init grantee variable.
qs_grantee_t grantee;
init_grantee (&grantee);

// fill grantee variable.
grantee.type = "group";
grantee.name = "QS_ALL_USERS";

// fill the grantee field of acl.
acl.grantee = &grantee;
acl.permission = "FULL_CONTROL";

// define and init acl list item variable, and fill the content field of acl.
qs_acl_item_t acl_item;
acl_item.content = &acl;

// init input acl field and append list node (a acl list item) to it.
qs_list_t acllist;
input.acl = &acllist;

qs_list_init (input.acl);
qs_list_append (&acl_item.node, input.acl);

QsError err = qs_put_bucket_acl(&input, &output, context_hdl);
if (QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
    printf("%d\n",output->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}
// Release output the when it is no longer needed.
release_put_bucket_acl_output(&output);
```

Put object with key
```c
qs_put_object_input_t input;
qs_put_object_output_t output;

// Initialize the input variable before calling the function
init_put_object_input(&input);

// Object content is come from a buffer.
long length = strlen("this is a test");
input.bodybuf = (char*)malloc( length );
memcpy(input.bodybuf,"this is a test",length);
input.content_length = &length;
input.bufLength = &length;

QsError err = qs_put_object(objectKey, &input, &output, context_hdl);
if ( QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
    printf("%d\n",output->response_code);
}

// Release heap memory you've just applied for input.
if(input.bodybuf)
{
    free(input.bodybuf);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}

// Release output the when it is no longer needed.
release_put_object_output(&output);
```

Delete object with key
```c
qs_delete_object_input_t input;
qs_delete_object_output_t output;

//Initialize the input variable before calling the function
init_delete_object_input(&input);

QsError err = qs_delete_object(objectkey, &input, &output, context_hdl);
if ( QS_ERR_NO_ERROR != err)
{
    // Print the HTTP status code.
    printf("%d\n",output->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}

//Release output the when it is no longer needed.
release_delete_object_output(&output);
```

Initialize Multipart Upload
```c
qs_initiate_multipart_upload_input_t input;
qs_initiate_multipart_upload_output_t output;

//Initialize the input variable before calling the function
init_initiate_multipart_upload_input(&input);

QsError err = qs_initiate_multipart_upload(objectkey, &input, &output, context_hdl);

if ( QS_ERR_NO_ERROR == err)
{
    // Print the HTTP status code.
    // Example: 200
    printf("%d\n",output->response_code);
    // Print the upload ID.
    // Example: "9d37dd6ccee643075ca4e597ad65655c"
    printf("%d\n",output.upload_id);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}

//Release output the when it is no longer needed.
release_initiate_multipart_upload_output(&output);
```

Upload Multipart
```c
// Upload The First Part
qs_upload_multipart_input_t input1;
qs_upload_multipart_output_t output1;

//Initialize the input variable before calling the function
init_upload_multipart_input(&input1);

printf(" |this is a Part 1| ");
long length = strlen(" |this is a Part 1| ");
int part_number = 1;
input1.bodybuf = (char *)malloc(length);
input1.bufLength = &length;
input1.content_length = &length;
input1.part_number = &part_number;
input1.upload_id = "9d37dd6ccee643075ca4e597ad65655c";

QsError err1 = qs_upload_multipart(objectkey, &input1, &output1, context_hdl);

if (QS_ERR_NO_ERROR == err1)
{
    // Print the HTTP status code.
    // Example: 201
    printf("%d\n",output1->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}
// Release heap memory you've just applied for input.
if(input1.bodybuf)
{
    free(input1.bodybuf);
}

// Release output the when it is no longer needed.
release_upload_multipart_output(&output1);

// Upload The Second Part
qs_upload_multipart_input_t input2;
qs_upload_multipart_output_t output2;

//Initialize the input variable before calling the function
init_upload_multipart_input(&input2);

printf(" |this is a Part 2| ");
long length = strlen(" |this is a Part 2| ");
int part_number = 2;
input2.bodybuf = (char *)malloc(length);
input2.bufLength = &length;
input2.content_length = &length;
input2.part_number = &part_number;
input2.upload_id = "9d37dd6ccee643075ca4e597ad65655c";

QsError err2 = qs_upload_multipart(objectkey, &input2, &output2, context_hdl);

if (QS_ERR_NO_ERROR == err2)
{
    // Print the HTTP status code.
    printf("%d\n",output2->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}
// Release heap memory you've just applied for input.
if(input2.bodybuf)
{
    free(input2.bodybuf);
}

// Release output the when it is no longer needed.
release_upload_multipart_output(&output2);
```

Complete Multipart Upload
```c
qs_complete_multipart_upload_input_t input;
qs_complete_multipart_upload_output_t output;

//Initialize the input variable before calling the function
init_complete_multipart_upload_input(&input);

input.object_parts = &object_parts_list;
input.upload_id = "9d37dd6ccee643075ca4e597ad65655c";

QsError err = qs_complete_multipart_upload(objectkey, &input, &output, context_hdl);
if (QS_ERR_NO_ERROR == err)
{
    // Print the HTTP status code.
    printf("%d\n",output->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}
//Release output the when it is no longer needed.
release_complete_multipart_upload_output(&output);
```

Abort Multipart Upload
```c
qs_abort_multipart_upload_input_t input;
qs_abort_multipart_upload_output_t output;

//Initialize the input variable before calling the function
init_abort_multipart_upload_input(&input);

input.upload_id = "9d37dd6ccee643075ca4e597ad65655c";

QsError err = qs_abort_multipart_upload(objectkey, &input, &output, context_hdl);
if (QS_ERR_NO_ERROR == err)
{
    // Print the HTTP status code.
    // Example: 400
    printf("%d\n",output->response_code);
}

if (QS_ERR_UNEXCEPTED_RESPONSE == err )
{
    printf("request_id = %s , with detail message : %s\n" , error_info.request_id, error_info.messag);
}
//Release output the when it is no longer needed.
release_abort_multipart_upload_output(&output);
```

