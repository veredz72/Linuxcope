fd=fopen('tio.bin', 'r');
%each row in tio.bin : id(uint32), val(uint32), timetag(uint64)

%extract id vector from file 
id = fread(fd, inf, 'uint32', 12); %skip 12 bytes (val(4) + timtag(8))
%extract timetag from file 
fseek (fd,8,"bof");
timetag = fread(fd, inf, 'uint64', 8); %skip 8 bytes (id(4) + val(4))

fclose (fd);

%create a talbe. column 1: id, column 2: timetag 
kernel = zeros (size(id,1),2);
kernel (:,1) = id;
kernel (:,2) = timetag;

fd=fopen('linuxcope.bin', 'r');
%each row in tio.bin : id(uint32), val(uint32), timetag(uint64)

%extract id vector from file 
id = fread(fd, inf, 'uint32', 12); %skip 12 bytes (val(4) + timtag(8))
%extract timetag from file 
fseek (fd,8,"bof");
timetag = fread(fd, inf, 'uint64', 8); %skip 8 bytes (id(4) + val(4))

fclose (fd);

user = zeros (size(id,1),2);
user (:,1) = id;
user (:,2) = timetag;

table = [kernel; user];
sorted = sortrows (table,2,'ascend');

id = sorted (:,1);
timetag = sorted (:,2);
count = 0;

for row=1:1:size(sorted,1)
    diff=0;
    if (id (row)==0)
        next = find(id(row+1:end)==1, 1, 'first');
        diff = timetag (next+row) - timetag (row);
    end
    
    if (id (row,1)==2)
        next = find(id(row+1:end)==3, 1, 'first');
        diff = timetag (next+row) - timetag (row);
    end
    if (diff>100000)
        count=count+1;
        diffvec(count)=diff;
    end
end
