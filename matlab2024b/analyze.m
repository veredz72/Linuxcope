clear all;
numLines = numel(readlines('dmesg.log'));
fid = fopen('dmesg.log', 'r');

id= zeros (numLines,1);
timestamp  = zeros (numLines,1);

cnt=1;

while ~feof(fid)
    line = fgetl(fid);
    vals = textscan(line, '[ %*f] %u64,%u64');
    id(cnt)=vals{1};
    timestamp(cnt)=vals{2};
    cnt=cnt+1;
end

cnt=1;
for row=1:1:numLines
    diff=0;
    if (id (row)==0)
       next = find(id(row+1:end)==1, 1, 'first');
       diff = timestamp (next+row) - timestamp (row);
    end

    if (id (row,1)==2)
       next = find(id(row+1:end)==3, 1, 'first');
       diff = timestamp (next+row) - timestamp (row);
    end

    if (diff>0)
        diffvec (cnt) = diff;
        cnt=cnt+1;
    end;
end

fclose (fid);




