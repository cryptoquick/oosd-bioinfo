function init() {
	makeXHR("POST", "seqs", null, fillseqs);
}

function fillseqs(seqdata) {
	var el = document.getElementById("seqs");
	var content = "";
	var seqs = JSON.parse(seqdata);
	
	for (var i = 0, ii = seqs.length; i < ii; i++) {
		content += '<a class="button" id="' + seqs[i] + '" onclick="seq(\'' + seqs[i] + '\')" href="#">' + seqs[i] + '</a>';
	}
	
	el.innerHTML = content;
}

var alg = "";

function select(type) {
	var nw = document.getElementById("nwbut");
	var msa = document.getElementById("msabut");
	var seqnum = document.getElementById("seqnum");
	
	if (type == "msa") {
		nw.className = "button";
		msa.className = "buttonhi";
		seqnum.innerText = "Select many to align." + " Not functional at the moment.";
		alg = "msa";
	}
	else if (type == "nw") {
		msa.className = "button";
		nw.className = "buttonhi";
		seqnum.innerText = "Select two to align.";
		alg = "nw";
	}
}

var seq_queue = [];

function seq(seqname) {
	var el = document.getElementById(seqname);
	
	if (seq_queue.length == 1 && alg == "nw") {
		seq_queue.push(seqname);
		el.className = "buttonhi";
	}
	else if (seq_queue.length == 2 && alg == "nw") {
		seq_queue.push(seqname);
		var gobut = document.getElementById("gobut");
		gobut.innerText = "Needleman Wunsch: " + seq_queue[0] + ", " + seq_queue[1];
		el.className = "buttonhi";
	}
	else if (alg == "msa") {
		seq_queue.push(seqname);
	}
	else {
		while(seq_queue.length > 0) {
			el = seq_queue.pop();
			el.className = "button";
		}
	}
}
