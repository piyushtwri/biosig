function HDR=eegchkhdr(HDR);
% EEGCHKHDR checks header information an 
% provides interactive dialog for missing Headerinformation
%
% HDR=eegchkhdr(HDR)
%
% see also: SOPEN, SREAD, SSEEK, STELL, SCLOSE, SWRITE

%	$Revision: 1.7 $
%	$Id: eegchkhdr.m,v 1.7 2004-02-12 15:03:15 schloegl Exp $
%	Copyright (c) 1997-2003 by Alois Schloegl
%	a.schloegl@ieee.org	


if nargin<1, HDR=[]; end;

if ~isfield(HDR,'FileName'),
        tmp = input('Whats the Filename? :');
        HDR.FileName = tmp;
end;

[HDR.FILE.Path,HDR.FILE.Name,FileExt] = fileparts(HDR.FileName);
if ~isfield(HDR,'TYPE'),
        HDR.TYPE = upper(FileExt(2:length(FileExt)));
end;

Answer='N';
if strcmp(HDR.TYPE,'BKR'),
        while ~strcmp(upper(Answer),'Y'),
                if ~isfield(HDR,'FileName'),
                        tmp = input('Whats the Filename? :');
                        HDR.FileName = tmp;
                end;
                
                if ~isfield(HDR,'SampleRate'),
                        tmp=input('Whats the sampling rate[Hz] :');
                        HDR.SampleRate=tmp;
                end;
                
                if ~isfield(HDR,'PhysMax'),
                        tmp=input('Whats the maximum physical value [�V]:');
                        HDR.PhysMax=tmp;
                end;
                if isempty(HDR.PhysMax), HDR.PhysMax=nan; end;
                
                if ~isfield(HDR,'DigMax'),
                        HDR.DigMax=2^15-1;
                end;
                if ~isfield(HDR,'Filter'),
                        HDR.Filter=[];
                end;
                if ~isfield(HDR.Filter,'LowPass'),
                        tmp=input('Whats the upper cutoff frequency?[Hz]:');
                        HDR.Filter.LowPass=tmp;
                end;
                if ~isfield(HDR.Filter,'HighPass'),
                        tmp=input('Whats the lower cutoff frequency?[Hz]:');
                        HDR.Filter.HighPass=tmp;
                end;
                                
                fprintf(1,'\n%% This demonstrates how the Header should be defined. \n');
                fprintf(1,'HDR.TYPE\t= ''BKR'';  %% (file format)\n');
                fprintf(1,'HDR.FileName\t= ''%s'';  %%(FileName)\n',HDR.FileName);
                fprintf(1,'HDR.SampleRate\t=%5i;  %%(Sampling rate [Hz])\n',HDR.SampleRate);
                fprintf(1,'HDR.PhysMax\t= %.3f; %%(Physical Maximum)\n',HDR.PhysMax);
                fprintf(1,'HDR.DigMax\t= %5i;  %%(Digital Maximum)\n',HDR.DigMax);
                fprintf(1,'HDR.Filter.LowPass\t=%5f;  %%(upper cutoff frequency)\n',HDR.Filter.LowPass(1));
                fprintf(1,'HDR.Filter.HighPass\t=%5f;  %%(lower cutoff frequency [Hz])\n',HDR.Filter.HighPass(1));
                
                if ~isfield(HDR,'FLAG'), 
                        tmp_flag = 0; 
                        ref_flag = 0;
                else 
                        tmp_flag = isfield(HDR.FLAG,'TRIGGERED');
                        ref_flag = isfield(HDR.FLAG,'REFERENCE');
                end; 
                if ~tmp_flag, 
                        HDR.FLAG.TRIGGERED = HDR.NRec>1;	% Trigger Flag
                end;
                if ~ref_flag, 
                        HDR.FLAG.REFERENCE = '';	% Trigger Flag
                end;
                %fprintf(1,'HDR.FLAG.TRIGGERED\t=%2i;  %%(FLAG TRIGGERED 0=OFF, 1=ON)\n',HDR.FLAG.TRIGGERED);
                fprintf(1,'HDR.FLAG.REFERENCE\t=''%3s'';  %% (COM, CAR: common average reference; LOC,LAR local average ref; LAP Laplacian derivation, WGT weighted average)\n',HDR.FLAG.REFERENCE);
                %A = input('Are all values correct [Y]/n?');
                Answer = 'Y';
        end;
        
elseif strcmp(HDR.TYPE,'EDF') 
        HDR.VERSION='0       ';
        
elseif strcmp(HDR.TYPE,'GDF') 
        HDR.VERSION='GDF     ';
        
elseif strcmp(HDR.TYPE,'BDF'),
        HDR.VERSION=[char(255),'BIOSEMI'];
        
end;
