# [Secure Sandbox Example](https://www.easefilter.com/Forums_Files/Secure-Sandbox.htm)
A sandbox is a secure, isolated and a tightly controlled environment where programs can be run and data can be protected. Sandboxes restrict what a piece of code can do, giving it just as many, permissions as it needs without adding additional permissions that could be abused.

## Prevent malicious or malfunctioning programs from running
Malware — short for malicious software — refers to various types of programs written with the purpose of gaining access to a computer for malicious intent, and often without the user’s knowledge. Malware comes in a variety of forms, such as viruses, spyware, adware, ransomware, and Trojans.There are a number of ways that your device can be infected with malware, but many times it comes from a malicious website, or open the attachment file from your email. By default, anything you download from a web browser will normally go to the %appdata% Downloads folder on your computer.

To prevent the malware from running in the first place, you can setup the sandbox with the policy which not allow the binaries inside the sandbox being launched for those folders where will store the malware, for example "C:\Users\Username\AppData\Local\Temp", "C:\Documents and Settings\ username \Local Settings\Temporary Internet Files". With the sandbox protection, you never have to worry about suspicious attachments or spear phishing attacks, you are safe to download the files from your web browser or you are safe to open your attachment from your email, because of the malware never be launched without your permission.

## Run untrusted Windows programs safely in EaseFilter Secure Sandbox
How many times have you downloaded an executable file, but were afraid to run it? Have you ever been in a situation which required a clean installation of Windows, but didn’t want to set up a virtual machine? With EaseFilter Secure Sandbox protection, now you can restrict the permission of the untrusted programs running, prevent the programs from changing, deleting your data, or modifying your registry key. So you can safely test and try these untrusted programs and applications within Sandbox and prevent unauthorized changes to your underlying system that may occur.

## Protect your confidential files in EaseFilter Secure Sandbox

The secure sandbox can setup a folder with secure access policies, it can encrypt your sensitive files inside the sandbox, prevent the files from being accessed or modified by unauthorized users or processes. It helps you protect valuable data from malicious apps and threats, such as ransomware. It protects your data by checking against a list of known, trusted processes. Secure folder access works by only allowing processes to access protected folders if the process is included on a list of trusted software. If a process isn't on the list, secure folder access will block it from making changes to files inside secure folders.

![Secure Sandbox](https://www.easefilter.com/images/secureSandboxScreenshot.png)

### Prevent or restrict the executable binaries running

1. Setup secure sandbox folder filter mask, i.e., c:\sandbox\*, this is the folder which the executable binaries located.
2. Allow the binaries being executed if you want to test the binaries, or disable the execution of the binaries to prevent the untrusted processes from running. For example, you can setup a sandbox for the download folder to prevent the untrusted download binaries from running.
3. If you allow the binaries to run, you can also allow or deny the binaries to access or change the registries. To protect the registries being changed by the binaries, you can disable the registries changing feature.
4. Setup the specific file access rights to different file folders for the process. By default, set the least access rights for all files to the process, then if you want to allow the process to access some specific folders, add these folders with specific rights to the process as the below image, allow the process with read access to the folder c:\windows, allow full rights access to the folder c:\mysandbox.

![file access rights](https://www.easefilter.com/images/process-file-access-rights.png)

### Protect your confidential files with sandbox

1. Setup the sandbox for the protected folder, i.e., c:\protectedFolder\*.
2. Setup the default access rights to the protected folder, i.e., add the least access rights to the protected folder, it meant only the authorized processes can access the protected folder.
3. Enable encryption for the protected folder, prevent the confidential files from being distributed to out of your company.
4. Add authorized processes to the protected folder, i.e., the below image shows that all processes which were launched from c:\windows folder were authorized to read the sandbox.

![Authorized processes](https://www.easefilter.com/images/AuthorizedProcesses.png)


## EaseFilter File System Filter Driver SDK Reference
| Product Name | Description |
| --- | --- |
| [Cloud File System SDK](https://www.easefilter.com/cloud/cloud-file-system-sdk.htm) | EaseFilter Cloud File System SDK Introduction. |
| [CloudTier Storage Tiering SDK](https://www.easefilter.com/cloud/storage-tiering-sdk.htm) | EaseFilter Storage Tiering Filter Driver SDK Introduction. |
| [File Monitor SDK](https://www.easefilter.com/kb/file-monitor-filter-driver-sdk.htm) | EaseFilter File Monitor Filter Driver SDK Introduction. |
| [File Control SDK](https://www.easefilter.com/kb/file-control-file-security-sdk.htm) | EaseFilter File Control Filter Driver SDK Introduction. |
| [File Encryption SDK](https://www.easefilter.com/kb/transparent-file-encryption-filter-driver-sdk.htm) | EaseFilter Transparent File Encryption Filter Driver SDK Introduction. |
| [Registry Filter SDK](https://www.easefilter.com/kb/registry-filter-drive-sdk.htm) | EaseFilter Registry Filter Driver SDK Introduction. |
| [Process Filter SDK](https://www.easefilter.com/kb/process-filter-driver-sdk.htm) | EaseFilter Process Filter Driver SDK Introduction. |
| [EaseFilter SDK Programming](https://www.easefilter.com/kb/programming.htm) | EaseFilter Filter Driver SDK Programming. |

## EaseFilter SDK Sample Projects
| Sample Project | Description |
| --- | --- |
| [CloudTier Storage Tiering Demo](https://www.easefilter.com/cloud/cloudtier-storage-tiering-demo.htm) | A HSM File System Filter Driver Demo. |
| [CloudTier S3 Tiering Demo](https://www.easefilter.com/cloud/cloudtier-s3-intelligent-tiering-demo.htm) | CloudTier S3 Intelligent Tiering Demo. |
| [Cloud File DR S3 Demo](https://www.easefilter.com/cloud/cloud-file-dr-demo.htm) | Cloud File DR S3 Demo. |
| [Amazon S3 File Explorer Demo](https://www.easefilter.com/cloud/s3-browser-demo.htm) | Amazon S3 File Explorer Demo. |
| [Auto File DRM Encryption](https://www.easefilter.com/kb/auto-file-drm-encryption-tool.htm) | Auto file encryption with DRM data embedded. |
| [Transparent File Encrypt](https://www.easefilter.com/kb/AutoFileEncryption.htm) | Transparent on access file encryption. |
| [Secure File Sharing with DRM](https://www.easefilter.com/kb/DRM_Secure_File_Sharing.htm) | Secure encrypted file sharing with digital rights management. |
| [File Monitor Example](https://www.easefilter.com/kb/file-monitor-demo.htm) | Monitor file system I/O in real time, tracking file changes. |
| [File Protector Example](https://www.easefilter.com/kb/file-protector-demo.htm) | Prevent sensitive files from being accessed by unauthorized users or processes. |
| [FolderLocker Example](https://www.easefilter.com/kb/FolderLocker.htm) | Lock file automatically in a FolderLocker. |
| [Process Monitor](https://www.easefilter.com/kb/Process-Monitor.htm) | Monitor the process creation and termination, block unauthorized process running. |
| [Registry Monitor](https://www.easefilter.com/kb/RegMon.htm) | Monitor the Registry activities, block the modification of the Registry keys. |
| [Secure Sandbox Example](https://www.easefilter.com/kb/Secure-Sandbox.htm) |A secure sandbox example, block the processes accessing the files out of the box. |
| [FileSystemWatcher Example](https://www.easefilter.com/kb/FileSystemWatcher.htm) | File system watcher, logging the file I/O events. |
| [ZeroTrust Example](https://www.easefilter.com/kb/zero-trust-file-access-control-demo.htm) | Zero trust file access control with encryption feature. |

## Filter Driver Reference

* [Understand MiniFilter Driver](https://www.easefilter.com/kb/understand-minifilter.htm)
* [Understand File I/O](https://www.easefilter.com/kb/File_IO.htm)
* [Understand I/O Request Packets(IRPs)](https://www.easefilter.com/kb/understand-irps.htm)
* [Filter Driver Developer Guide](https://www.easefilter.com/kb/DeveloperGuide.htm)
* [MiniFilter Filter Driver Framework](https://www.easefilter.com/kb/minifilter-framework.htm)
* [Isolation Filter Driver](https://www.easefilter.com/kb/Isolation_Filter_Driver.htm)

## Support
If you have questions or need help, please contact support@easefilter.com 

[Home](https://www.easefilter.com/) | [Solution](https://www.easefilter.com/solutions.htm) | [Download](https://www.easefilter.com/download.htm) | [Demos](https://www.easefilter.com/online-fileio-test.aspx) | [Blog](https://blog.easefilter.com/) | [Programming](https://www.easefilter.com/kb/programming.htm)
