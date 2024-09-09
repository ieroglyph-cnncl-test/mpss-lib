This task is to define an interface and implement a derived class in C++ that fetches the latest Ubuntu Cloud image information in Simplestreams format from
https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json
and provides methods that:

* Return a list of all currently supported Ubuntu releases.
* Return the current Ubuntu LTS version.
* Return the sha256 of the disk1.img item of a given Ubuntu release.

This will be wrapped in a CLI that outputs the above returned values depending on the option given.

The definition of the Simplestreams format is found at
https://canonical-simplestreams.readthedocs-hosted.com/en/latest/reference/streams-product-jsonschema/#jsonschema-product.

You need only be concerned with the amd64 architecture for the cloud images. 
You may choose to use a third party JSON parser and HTTP downloader library if you wish.